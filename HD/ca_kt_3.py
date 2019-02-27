# ca_kt v1.3 modify measurement CA or KT or CA_KT

import time
import csv
from datetime import datetime, timedelta
import datetime
import test5_1
import glob
import serial
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
        ports = [s for s in result if "COM9" in s]
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

def time_run(delay, repeat, mode = None): #mode 0:CA 1:KT 2:CA_KT
    oc = OC()
    ser = oc.ca_init()

    kt = test5_1
    serk = kt.KT().keithley_init()
        
    f = open('time_meas.csv', 'w')
    wr = csv.writer(f)

    if mode == 0:
        wr.writerow(["repeat", "Date", "Time", "x", "y", "lv"])
    elif mode == 1:
        wr.writerow(["repeat", "Date", "Time", "value", "units"])
    elif mode == 2:
        wr.writerow(["repeat", "Date", "Time", "x", "y", "lv", "value", "units"])

    if mode != 0:
        VI = kt.KT().measure(serk, 2)
        if VI[1] != 'ADC':             #signal miss overlap just PC com #DCI:current(ADC) DCV:voltage(VDC)
            kt.KT().set_system_key(serk, 'DCI')
            kt.KT().measure(serk, 2)

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
                        kt_ms = kt.KT().measure(serk, 1)  # raw:1 auto:2
                        value = kt_ms[0]
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
                        kt_ms = kt.KT().measure(serk,1) # raw:1 auto:2
                        value = kt_ms[0]
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
                        kt_ms = kt.KT().measure(serk, 1)  # raw:1 auto:2
                        value = kt_ms[0]
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
                        kt_ms = kt.KT().measure(serk, 1)  # raw:1 auto:2
                        value = kt_ms[0]
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
                print("repeat:%s Date:%s Time:%s X:%s Y:%s lv:%s val:%.3f units:%s " %(repeat,nowDate, nowTime, x, y, lv, value, units))
                wr.writerow([repeat,nowDate, nowTime, x, y, lv, value, units])
            repeat -= 1
        break
    print('stability_completed')

def set_system_key(system_key):  # D/S 355 page
    kt = test5_1
    serk = kt.KT().keithley_init()
    if system_key != '':
        kt.KT().set_system_key(serk, system_key)
    else:
        print("Unknown system setting!")
        return None