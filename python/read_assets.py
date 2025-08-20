import openpyxl

from json_data_io import writeJsonData
from read_data import get_end_of_row, read_columns_data


def read_well_test_data():

    file_path = "data/Production Data/September 2020/1, 2020.xlsx"
    sheet_name = "WellTest"
    wb = openpyxl.load_workbook(file_path)  # Modify the path as necessary
    sheet = wb[sheet_name]
    start_row = 3
    start_col = 1
    end_col = 20
    well_test_data = []

    colum_headers = read_columns_data(sheet, 1, start_col, end_col)
    endRow = get_end_of_row(start_row, start_col, sheet)
    for i in range(start_row, endRow + 1):
        row_data = read_columns_data(sheet, i, start_col, end_col)
        r_data = {}
        for j in range(0, end_col):
            r_data[colum_headers[j]] = row_data[j]

        well_test_data.append(r_data)

    well_test_json_data_file_path = "data/Production Data/September 2020/1_2020.json"
    writeJsonData(well_test_json_data_file_path, well_test_data)

read_well_test_data()

