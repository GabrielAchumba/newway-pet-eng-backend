import json
import pandas as pd

def readJsonData(file_name):
    with open(file_name, 'r') as file:
        json_data = json.load(file)

    return json_data

def writeJsonData(file_name, data):

    # Writing the list to a JSON file
    with open(file_name, 'w') as json_file:
        json.dump(data, json_file, indent=4)

    print(f"Json data written to {file_name}")


def writeJsonDataToMSExscel(json_data_list, excel_file_path):

    # Convert JSON to DataFrame
    df = pd.DataFrame(json_data_list)

    # Save to Excel
    #excel_filename = "forecast_data.xlsx"
    df.to_excel(excel_file_path, index=False)

    print(f"Data successfully exported to {excel_file_path}")
