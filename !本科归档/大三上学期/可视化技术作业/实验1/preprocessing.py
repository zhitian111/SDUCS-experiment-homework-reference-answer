import csv as csv


def read_csv(file_path):
    with open(file_path, "r", encoding="utf-8") as f:
        reader = csv.reader(f)
        data = [row for row in reader]
    return data


age_list = [i for i in range(0, 91, 5)]
year_list = ["1900", "2000"]


if __name__ == "__main__":
    data = read_csv("./census2000.csv")
    # { age: "41-50", male: 630, female: 660 },
    for year in year_list:
        if year == "1900":
            print("const data1 = [")
        if year == "2000":
            print("const data2 = [")
        for age in age_list:
            male = 0
            female = 0
            for row in data:
                if str(age) == row[2] and row[0] == "1" and row[1] == year:
                    male = row[3]
                if str(age) == row[2] and row[0] == "2" and row[1] == year:
                    female = row[3]
            if age != 90:
                buffer = f'{{ age: "{age}-{age+5-1}", male: {male}, female: {female} }},'
            else:
                buffer = f'{{ age: "{age}以上", male: {male}, female: {female} }}'
            print(buffer)
        print(']')
        print('\n\n')