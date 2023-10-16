import csv

# Read id.csv and create a mapping of states to IDs
state_id_mapping = {}
with open('id.csv', mode='r', newline='') as id_file:
    id_reader = csv.reader(id_file)
    for row in id_reader:
        state_id_mapping[row[1]] = row[0]


# Read input.csv, replace states with IDs, and write to output.csv
with open('input.csv', mode='r', newline='') as input_file, open('output.csv', mode='w', newline='') as output_file:
    input_reader = csv.reader(input_file)
    output_writer = csv.writer(output_file)

    for row in input_reader:
        if row[0] in state_id_mapping:
            row[0] = state_id_mapping[row[0]]
        if row[1] in state_id_mapping:
            row[1] = state_id_mapping[row[1]]
        output_writer.writerow(row)
