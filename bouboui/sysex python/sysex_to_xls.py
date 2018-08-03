from openpyxl import load_workbook
import pastel

print("DX7 Sysex Python Tool")
sysex = input(pastel.colorize('<fg=white;options=bold>Sysex file : '))
header_file = open('cartridge.h', "w")
xls = load_workbook('cartridge.xlsx')



print(xls.get_sheet_names())
ws1 = xls.active
ws1['B2'] = 32
ws1.title = "DX7 ROM CARTRIDGE"
xls.save("cartridge.xlsx")