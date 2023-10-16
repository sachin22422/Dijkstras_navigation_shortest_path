import csv
from geopy.distance import great_circle
from itertools import combinations

# Read the states.csv file
with open('states.csv', 'r') as file:
    reader = csv.DictReader(file)
    states_data = list(reader)

# Create a list of unique state names
state_names = set(row['State'] for row in states_data)

# Calculate distances between all state pairs
state_distances = []
for state1, state2 in combinations(state_names, 2):
    lat_lon1 = [float(row['Latitude']) for row in states_data if row['State'] == state1][0], [float(row['Longitude']) for row in states_data if row['State'] == state1][0]
    lat_lon2 = [float(row['Latitude']) for row in states_data if row['State'] == state2][0], [float(row['Longitude']) for row in states_data if row['State'] == state2][0]
    distance = int(great_circle(lat_lon1, lat_lon2).kilometers)
    state_distances.append((state1, state2, distance))

# Save the distances to a CSV file
with open('indian_states_distances.csv', 'w', newline='') as output_file:
    fieldnames = ['Source', 'Destination', 'Distance']
    writer = csv.DictWriter(output_file, fieldnames=fieldnames)
    writer.writeheader()
    for source, destination, distance in state_distances:
        writer.writerow({'Source': source, 'Destination': destination, 'Distance': distance})

print("Distance calculation and saving to 'indian_states_distances.csv' complete.")
