# HD graytrackinglog final version

import os
import csv
import datetime
class HD():
    def graytrackinglog(self):
        if os.path.isfile("OC_meas_log.csv"):
            print "Yes file"

            # csv file write
            r1 = open('OC_meas_log.csv', 'r')
            OC_para_C = list(csv.reader(r1))
            y_OC_para_C = len(OC_para_C)
            x_OC_para_C = len(OC_para_C[0])

            # tracking
            f = open('OC_meas_log.csv', 'ab', )
            wr = csv.writer(f)

            now = datetime.datetime.now()
            nowDate = now.strftime('%Y-%m-%d')
            nowTime = now.strftime('%H:%M:%S')
            wr.writerow([nowDate, nowTime, "", ""])
            wr.writerow(["gray", "x", "y", "lv"])
            gray = 5
            for i in range(1, gray, +1):
                x = gray
                y = 1
                lv = 100
                wr.writerow([i, x, y, lv])
            f.close()

            # tracking + original reading
            c = open('OC_meas_log.csv', 'r')
            OC_para = list(csv.reader(c))
            cnt_OC_para = len(OC_para)

            # list array and write
            OC_para_D = OC_para[y_OC_para_C:cnt_OC_para]
            cnt_OC_para_D = len(OC_para_D)

            if cnt_OC_para_D > y_OC_para_C :
                y_OC_para_C = cnt_OC_para_D - y_OC_para_C
                for i in range(0,y_OC_para_C):
                    OC_para_C.append(['']*x_OC_para_C)
                for r, c in zip(range(0, len(OC_para_C), +1), range(0, len(OC_para_D), +1)):
                    OC_para_C[r] = OC_para_C[r] + OC_para_D[c]
            elif cnt_OC_para_D <= y_OC_para_C:
                for i in range(cnt_OC_para_D, y_OC_para_C, +1):
                    OC_para_D.append(['', '', '', ''])
                for r, c in zip(range(0, len(OC_para_C), +1), range(0, len(OC_para_D), +1)):
                    OC_para_C[c] = OC_para_C[r] + OC_para_D[c]
            f = open('OC_meas_log.csv', 'wb')
            a = csv.writer(f)
            a.writerows(OC_para_C)
            f.close()

        else:
            print "NO file"
            # tracking
            f = open('OC_meas_log.csv', 'ab', )
            wr = csv.writer(f)

            now = datetime.datetime.now()
            nowDate = now.strftime('%Y-%m-%d')
            nowTime = now.strftime('%M:%S')
            wr.writerow([nowDate, nowTime, "", ""])
            wr.writerow(["gray", "x", "y", "lv"])
            gray = 6
            for i in range(1, gray, +1):
                x = gray
                y = 1
                lv = 100
                wr.writerow([i, x, y, lv])
            f.close()


