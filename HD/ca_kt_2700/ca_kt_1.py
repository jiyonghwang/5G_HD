# ca_kt v1.4 CA_KT keithley2700 final

import time
import csv
from datetime import datetime, timedelta
import datetime
import glob
import serial
import platform
import sys
global ser
from decimal import Decimal

class OC():
    def serial_ports(self):
        if sys.platform.startswith('win'):
            ports = ['COM%s' % (i + 1) for i in range(256)]
        elif sys.platform.startswith('linux') or sys.platform.startswith('cygwin'):
            ports = glob.glob('/dev/tty[A-Za-z]*')
        elif sys.platform.startswith('darwin'):
            ports = glob.glob('/dev/tty.*')
        else:
            raise EnvironmentError('Unsupported platform')

        result = []
        for port in ports:
            try:
                s = serial.Serial(port)
                s.close()
                result.append(port)
            except (OSError, serial.SerialException):
                pass
        ports = [s for s in result if "COM12" in s]  #window COM@   IOS usbserial-A907RK9V
        return ports

    def ca_init(self):
        ports_l = self.serial_ports()
        for port in ports_l:
            seri = serial.Serial(port, baudrate = 38400, bytesize = 7, stopbits = 2, parity = 'E')
            seri.write("COM,1\r\n")
            out = ''
            time.sleep(0.2)
            while seri.inWaiting() > 0:
                out += seri.read(1)
            if 'OK00' in out:
                print('CA-310 OK')
                return seri
        print('CA-310 Connection Fail')

    def ca_measure(self, ser):
        for i in range(0, 4, 1):
            ser.write("MES\r\n")
            out = ''
            time.sleep(0.11)
            #print(ser)
            while ser.inWaiting() > 0:
                out += ser.read(1)
            if out != '':
                x = out[8:12]
                y = out[13:17]
                lv = out[18:23]
                if x == '' or y == '' or lv == '':
                    pass
                else:
                    x_test = Decimal(x) / 10000
                    y_test = Decimal(y) / 10000
                    lv_test = Decimal(lv)
                    #print("0 X: %s / Y: %s / Lv: %s" % (x_test, y_test, lv_test))
                    return [x_test, y_test, lv_test]
            elif i == 3:
                print("CA-310 Read Error")
                x_test = Decimal(0)
                y_test = Decimal(0)
                lv_test = Decimal(0)
                #print("1 X: %s / Y: %s / Lv: %s" % (x_test, y_test, lv_test))
                return [x_test, y_test, lv_test]

class KT():
    def serial_ports(self):
        if sys.platform.startswith('win'):
            ports = ['COM%s' % (i + 1) for i in range(256)]
        elif sys.platform.startswith('linux') or sys.platform.startswith('cygwin'):
            ports = glob.glob('/dev/tty[A-Za-z]*')
        elif sys.platform.startswith('darwin'):
            ports = glob.glob('/dev/tty.*')
        else:
            raise EnvironmentError('Unsupported platform')

        result = []
        for port in ports:
            try:
                s = serial.Serial(port)
                s.close()
                result.append(port)
            except (OSError, serial.SerialException):
                pass
        ports = [s for s in result if "COM11" in s] #window COM@   IOS usbserial-A907RK9V
        return ports

    def keithley_init(self):
        ports_l = self.serial_ports()
        for port in ports_l:
            seri = serial.Serial(port, baudrate = 19200, bytesize = 8, stopbits = 1, parity = 'N')
            time.sleep(0.2)
            print('Keithley OK')
            return seri
        print('Connection Fail')

    def open_serial(self, ser):
        ser.open()

    def close_serial(self, ser):
        ser.close()

    def read(self, ser):
        out = []
        terminated = False
        #print(ser)
        while ser.inWaiting() > 0 or not terminated:
            data = str(ser.read(1))
            if data == '\r':
                out.append('\n')
                terminated = True
            else:
                out.append(data)
        #print("2",out)
        if out != '':
            return ' '.join(out)
        else:
            return ''

    def write_and_read(self, ser, command, pause = .25):
        ser.write(command + '\r')
        time.sleep(pause)
        return self.read(ser)

    def get_response(self, ser, command, pause = .25):
        if ser.isOpen():
            response = self.write_and_read(ser, command, pause = pause)
            if response != '':
                return response
            else:
                return None
        else:
            print("Port is closed...")

    def measure(self, ser, command):  # command D/S 414page
        if command == 1:
            meas1 = self.get_response(ser, ':FETCh?')  # no math function enabled
            #print(meas1) #full meas          #D/S 349 page
            value = meas1[0:30]
            words_value = value.split()
            words_sum_value = "".join(words_value)
            words_f_value = float(words_sum_value)
            units = meas1[30:36]
            words_units = units.split()
            words_sum_units = "".join(words_units)
            #print(meas1[0:30]) #value
            #print(meas1[30:36]) #Units : VDC(DC Volts) VAC(AC Volts) ADC(DC Current) AAC(AC Current)
            #print(meas1[37:64]) #Timestamp
            #print(meas1[67:88]) #ReadingNumber
            return [words_f_value, words_sum_units]
        elif command == 2:
            meas2 = self.get_response(ser, ':MEASure?')  # one-shot meas mode math function enabled (Auto)
            #print(meas2)
            value = meas2[0:30]
            words_value = value.split()
            words_sum_value = "".join(words_value)
            words_f_value = float(words_sum_value)
            units = meas2[30:36]
            words_units = units.split()
            words_sum_units = "".join(words_units)
            #print(meas2[0:30])  #value
            # print(meas2[30:36]) #Units
            # print(meas2[0:1]) #value + -
            # print(str(meas2[2:4]))  # value + -
            # if meas2[0:1] == '-':
            #     print('neg')
            # print(meas2[37:64]) #Timestamp
            # print(meas2[67:88]) #ReadingNumber
            #print([words_sub_value, words_sub_units])
            return [words_f_value, words_sum_units]
        else:
            print("Unknown measure setting!")
            return None

    def send_command(self, ser, command):
        if ser.isOpen():
            response = ser.write(command + '\r')
            if response != '':
                return response
            else:
                return None
        else:
            print("Port is closed...")

    def set_system_key(self, ser, system_key):           # D/S 355 page
        if system_key == 'DCV':
            ser.write(':SYSTem:KEY 2' + '\r')
        elif system_key == 'ACV':
            ser.write(':SYSTem:KEY 3' + '\r')
        elif system_key == 'DCI':
            ser.write(':SYSTem:KEY 4' + '\r')
        elif system_key == 'ACI':
            ser.write(':SYSTem:KEY 5' + '\r')
        elif system_key == 'ohm2':
            ser.write(':SYSTem:KEY 6' + '\r')
        elif system_key == 'ohm4':
            ser.write(':SYSTem:KEY 7' + '\r')
        elif system_key == 'FREQ':
            ser.write(':SYSTem:KEY 8' + '\r')
        elif system_key == 'TEMP':
            ser.write(':SYSTem:KEY 16' + '\r')
        elif system_key == 'RANGEUP':
            ser.write(':SYSTem:KEY 11' + '\r')
        elif system_key == 'RANGEDOWN':
            ser.write(':SYSTem:KEY 13' + '\r')
        elif system_key == 'AUTO':
            ser.write(':SYSTem:KEY 12' + '\r')
        elif system_key == 'RATE':
            ser.write(':SYSTem:KEY 31' + '\r')
        else:
            print("Unknown sensor setting!")
            return None

class HD():
    def time_run(self,delay, repeat, mode = None): #mode 0:CA 1:KT 2:CA_KT

        if mode == 0:
            oc = OC()
            ser = oc.ca_init()
        elif mode == 1:
            serk = KT().keithley_init()
        elif mode == 2:
            oc = OC()
            ser = oc.ca_init()
            serk = KT().keithley_init()

        f = open('time_meas.csv', 'wb')
        wr = csv.writer(f)

        if mode == 0:
            wr.writerow(["repeat", "Date", "Time", "x", "y", "lv"])
        elif mode == 1:
            wr.writerow(["repeat", "Date", "Time", "value", "units"])
        elif mode == 2:
            wr.writerow(["repeat", "Date", "Time", "x", "y", "lv", "value", "units"])

        if mode != 0:
            VI = KT().measure(serk, 2)
            if VI[1] != 'ADC':             #signal miss overlap just PC com #DCI:current(ADC) DCV:voltage(VDC)
                KT().set_system_key(serk, 'DCI')
                KT().measure(serk, 2)

        print('stability_Start')

        while True:
            now = datetime.datetime.now()
            nowDate = now.strftime('%Y-%m-%d')
            repeat1 = repeat
            while repeat > 0:
                Vtime = now + timedelta(seconds = delay)
                while True:
                    now = datetime.datetime.now()

                    if repeat == repeat1:
                        if mode == 0:
                            ser.close()
                            ser.open()
                            ca_ms = oc.ca_measure(ser)
                            x = ca_ms[0]
                            y = ca_ms[1]
                            lv = ca_ms[2]

                        elif mode == 1:

                            serk.close()
                            serk.open()
                            kt_ms = KT().measure(serk, 1)  # raw:1 auto:2
                            value = kt_ms[0]*1000
                            units = kt_ms[1]

                        elif mode == 2:

                            ca_ms = oc.ca_measure(ser)
                            x = ca_ms[0]
                            y = ca_ms[1]
                            lv = ca_ms[2]
                            ser.close()

                            kt_ms = KT().measure(serk,1) # raw:1 auto:2
                            value = kt_ms[0]*1000
                            units = kt_ms[1]
                        break

                    elif now >= Vtime:
                        if mode == 0:
                            ser.close()
                            ser.open()
                            ca_ms = oc.ca_measure(ser)
                            x = ca_ms[0]
                            y = ca_ms[1]
                            lv = ca_ms[2]

                        elif mode == 1:

                            serk.close()
                            serk.open()
                            kt_ms = KT().measure(serk, 1)  # raw:1 auto:2
                            value = kt_ms[0]*1000
                            units = kt_ms[1]

                        elif mode == 2:
                            ser.close()
                            ser.open()
                            ca_ms = oc.ca_measure(ser)
                            x = ca_ms[0]
                            y = ca_ms[1]
                            lv = ca_ms[2]

                            serk.close()
                            serk.open()
                            kt_ms = KT().measure(serk, 1)  # raw:1 auto:2
                            value = kt_ms[0]*1000
                            units = kt_ms[1]
                        break
                nowTime = now.strftime('%H:%M:%S.%f')[:-3]
                if mode == 0:
                    print("repeat:%s Date:%s Time:%s X:%s Y:%s lv:%s" %(repeat,nowDate, nowTime, x, y, lv))
                    wr.writerow([repeat,nowDate, nowTime, x, y, lv])
                elif mode == 1:
                    print("repeat:%s Date:%s Time:%s val:%.3f units:%s " %(repeat,nowDate, nowTime, value, units))
                    wr.writerow([repeat,nowDate, nowTime, value, units])
                elif mode == 2:
                    print("repeat:%s Date:%s Time:%s X:%s Y:%s lv:%s val:%.3f units:VDC " %(repeat,nowDate, nowTime, x, y, lv, value, units))
                    wr.writerow([repeat,nowDate, nowTime, x, y, lv, value, units])
                repeat -= 1
            break
        print('stability_completed')

    def set_system_key(self,system_key):  # D/S 355 page
        serk = KT().keithley_init()
        if system_key != '':
            KT().set_system_key(serk, system_key)
        else:
            print("Unknown system setting!")
            return None