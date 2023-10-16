import heapq
import csv


class Edge:
    def __init__(self, u, v, w):
        self.u = u
        self.v = v
        self.w = w
        
def read_edges_from_csv(file_path):
    edges = []
    with open(file_path, 'r') as csvfile:
        csvreader = csv.reader(csvfile)
        next(csvreader)  # Skip the header row
        for row in csvreader:
            u, v, w = map(int, row)
            edges.append(Edge(u, v, w))
    return edges

def read_node_names_from_csv(file_path):
    node_names = {}
    with open(file_path, 'r') as csvfile:
        csvreader = csv.reader(csvfile)
        for row in csvreader:
            node_id, node_name = row
            node_names[int(node_id)] = node_name
    return node_names

def add_edge(adj, edge):
    adj[edge.u].append(edge)
    adj[edge.v].append(edge)

def dijkstra(adj, src, dest):
    N = len(adj)
    dist = [float('inf')] * N
    dist[src] = 0
    pq = [(0, src)]
    from_node = [-1] * N
    from_node[src] = src

    while pq:
        distance, node = heapq.heappop(pq)
        if distance > dist[node]:
            continue
        for edge in adj[node]:
            other = edge.u if edge.v == node else edge.v
            w = edge.w
            if dist[node] + w < dist[other]:
                dist[other] = dist[node] + w
                heapq.heappush(pq, (dist[other], other))
                from_node[other] = node

    shortest_path = []
    while dest != from_node[dest]:
        shortest_path.append(dest)
        dest = from_node[dest]
    shortest_path.append(src)
    shortest_path.reverse()
    
    return dist, shortest_path

if __name__ == "__main__":
    csv_file_path = 'edges.csv'  # Replace with your CSV file path for edge information
    node_names_csv_file_path = 'id.csv'  # Replace with your CSV file path for node names
    
    edges = read_edges_from_csv(csv_file_path)
    node_names = read_node_names_from_csv(node_names_csv_file_path)
    
    max_node = max(max(edge.u, edge.v) for edge in edges)
    N = max_node + 1
    adj = [[] for _ in range(N)]
    
    for edge in edges:
        add_edge(adj, edge)

    src_name = input("Type your Starting State: ")
    dest_name = input("Type your Destination State: ")
    
    # Convert node names to IDs
    src = next(key for key, value in node_names.items() if value == src_name)
    dest = next(key for key, value in node_names.items() if value == dest_name)

    distances, path = dijkstra(adj, src, dest)
    
    print(f"Shortest Distance: {src_name} -> {dest_name} : {distances[dest]}")
    
    # Convert node IDs to names in the shortest path
    shortest_path_names = [node_names[node_id] for node_id in path]
    print("Shortest Path:", " -> ".join(shortest_path_names))
