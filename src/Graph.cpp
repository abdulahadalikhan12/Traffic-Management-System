#include "../src/Graph.h"
#include "../src/MinHeap.h"
#include "../src/Vehicle.h"
#include "../src/Queue.h"

/* ROAD CLASS */

// constructor
Road::Road(char src, char dest, int travelTime) : src(src), dest(dest), travelTime(travelTime), next(nullptr), status(1)
{
    // Status defaults to 1 (Clear) when the road is created
}

// getter and setters for status
int Road::getStatus() { return status; }

void Road::setStatus(int status) { this->status = status; }

std::string Road::getStatusString()
{
    if (status == 1)
        return "Clear";
    else if (status == 2)
        return "Blocked";
    else if (status == 3)
        return "Under Repair";
    else
        return "Unknown";
}

/* INTERSECTION CLASS */

// constructor
Intersection::Intersection(char name, int greenTime)
    : name(name), greenTime(greenTime), congestionLevel(0), emergencyFlag(false), roads(nullptr), vehicles(nullptr), next(nullptr)
{
    // Default values for congestionLevel and emergencyFlag are set here.
    // roads and vehicles are pointers to linked lists, initialized to nullptr
}
// add vehicle to the intersection
void Intersection::addVehicle(Vehicle *&vehicle)
{
    if (vehicles == nullptr)
    {
        vehicles = vehicle;
    }
    else
    {
        Vehicle *temp = vehicles;
        while (temp->next)
        {
            temp = temp->next;
        }
        temp->next = vehicle;
    }
}

// remove vehicle from the intersection
void Intersection::removeVehicle(const std::string &name)
{
    Vehicle *temp = vehicles;
    Vehicle *prev = nullptr;

    while (temp)
    {
        if (temp->name == name)
        {
            if (prev)
                prev->next = temp->next;
            else
                vehicles = temp->next;
        }
        prev = temp;
        temp = temp->next;
    }
}

// print all vehicles at the intersection
void Intersection::printVehicles()
{
    Vehicle *temp = vehicles;
    while (temp)
    {
        temp->printVehicle();
        temp = temp->next;
    }
}

void Intersection::incrementCongestionLevel()
{
    congestionLevel++;
}

void Intersection::decrementCongestionLevel()
{
    congestionLevel--;
}

/* GRAPH CLASS */

// constructor
Graph::Graph()
{
    for (int i = 0; i < MAX_INTERSECTIONS; ++i)
    {
        intersections[i] = nullptr;
    }
}

// add a new intersection
void Graph::addIntersection(char name, int greenTime)
{
    int index = name - 'A'; // map 'A' to 0, 'B' to 1, ..., 'Z' to 25
    if (index < 0 || index >= MAX_INTERSECTIONS)
    {
        std::cout << "Invalid intersection name!" << std::endl;
        return;
    }

    if (intersections[index] == nullptr)
    {
        intersections[index] = new Intersection(name, greenTime);
    }
}

// find an intersection by its name
Intersection *Graph::findIntersection(char name)
{
    int index = name - 'A';
    if (index < 0 || index >= MAX_INTERSECTIONS)
    {
        return nullptr;
    }
    return intersections[index];
}

// add a road between two intersections
void Graph::addRoad(char from, char to, int travelTime)
{
    Intersection *fromIntersection = findIntersection(from);
    Intersection *toIntersection = findIntersection(to);

    // if the 'from' intersection doesn't exist, add it
    if (!fromIntersection)
    {
        addIntersection(from);
        fromIntersection = findIntersection(from);
    }

    // if the 'to' intersection doesn't exist, add it
    if (!toIntersection)
    {
        addIntersection(to);
        toIntersection = findIntersection(to);
    }

    // create and add the road to the 'from' intersection's list of roads
    Road *newRoad = new Road(from, to, travelTime);
    newRoad->next = fromIntersection->roads;
    fromIntersection->roads = newRoad;
}

// visualize the city traffic network (intersection names and their roads)
void Graph::visualizeNetwork()
{
    for (int i = 0; i < MAX_INTERSECTIONS; ++i)
    {
        if (intersections[i])
        {
            std::cout << intersections[i]->name << " -> ";
            Road *road = intersections[i]->roads;
            while (road)
            {
                std::cout << "(" << road->dest << ", " << road->travelTime << "s) ";
                road = road->next;
            }
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
}

// visualize the traffic signals (intersection names and their green light times)
void Graph::visualizeSignals()
{
    for (int i = 0; i < MAX_INTERSECTIONS; i++)
    {
        if (intersections[i])
        {
            std::cout << intersections[i]->name << " -> " << intersections[i]->greenTime << "s" << std::endl;
        }
    }
    std::cout << std::endl;
}

// create intersections from a CSV file
bool Graph::createIntersections(const std::string &fileName)
{
    std::ifstream file(fileName);
    if (!file)
    {
        std::cout << "Error opening file!" << std::endl;
        return false;
    }

    std::string line;
    while (getline(file, line))
    {
        char name;
        int greenTime;
        if (sscanf(line.c_str(), "%c,%d", &name, &greenTime) == 2) // parsing (char,int)
        {
            addIntersection(name, greenTime);
        }
    }

    file.close();
    return true;
}

// create roads between intersections from a CSV file
bool Graph::createNetwork(const std::string &fileName)
{
    std::ifstream file(fileName);
    if (!file)
    {
        std::cout << "Error opening file!" << std::endl;
        return false;
    }

    std::string line;
    while (getline(file, line))
    {
        char from, to;
        int travelTime;
        if (sscanf(line.c_str(), "%c,%c,%d", &from, &to, &travelTime) == 3) // parsing (char,char,int)
        {
            addRoad(from, to, travelTime);
        }
    }

    file.close();
    return true;
}

// create vehicles from a CSV file
bool Graph::createVehicles(const std::string &fileName)
{
    std::ifstream file(fileName);
    if (!file)
    {
        std::cout << "Error opening file!" << std::endl;
        return false;
    }

    std::string line;
    // skip first line
    getline(file, line);
    while (getline(file, line))
    {
        char *nameBuffer = new char[10];
        char start, end;

        if (sscanf(line.c_str(), "%[^,],%c,%c", nameBuffer, &start, &end) == 3) // parsing (string,char,char)
        {
            Intersection *startIntersection = findIntersection(start);
            Intersection *endIntersection = findIntersection(end);
            std::string vehicleName(nameBuffer);
            delete[] nameBuffer;

            if (startIntersection && endIntersection)
            {
                Vehicle *newVehicle = new Vehicle(vehicleName, start, end);
                startIntersection->addVehicle(newVehicle);
                startIntersection->incrementCongestionLevel();
            }
            else
            {
                std::cerr << "Error: Invalid intersection names for vehicle " << vehicleName << std::endl;
            }
        }
        else
        {
            std::cerr << "Error: Invalid format in file at line: " << line << std::endl;
        }
    }

    file.close();
    return true;
}

// print all vehicles at all intersections
void Graph::printAllVehicles()
{
    for (int i = 0; i < MAX_INTERSECTIONS; i++)
    {
        if (intersections[i])
        {
            std::cout << "Intersection " << intersections[i]->name << std::endl;
            intersections[i]->printVehicles();
        }
    }
    std::cout << std::endl;
}

// Dijkstra's algorithm to find the shortest path between two intersections
void Graph::dijkstra(char start, char end)
{
    int dist[MAX_INTERSECTIONS];         // distance array
    int parent[MAX_INTERSECTIONS];       // parent array for path reconstruction
    bool visited[MAX_INTERSECTIONS];     // visited array
    MinHeap<char>::Node node;            // MinHeap Node structure
    MinHeap<char> pq(MAX_INTERSECTIONS); // Min-Heap priority queue

    std::fill(dist, dist + MAX_INTERSECTIONS, INT_MAX);     // init distances to infinity
    std::fill(visited, visited + MAX_INTERSECTIONS, false); // init visited array to false
    std::fill(parent, parent + MAX_INTERSECTIONS, -1);      // init parent array to -1

    int startIndex = start - 'A';
    int endIndex = end - 'A';

    dist[startIndex] = 0;

    // single-source shortest path
    pq.insert({0, start}); // insert the source node into the priority queue

    while (!pq.isEmpty())
    {
        auto current = pq.extractMin();
        char u = current.data; // intersection name
        int uIndex = u - 'A';

        if (visited[uIndex])
            continue; // skip if already visited
        visited[uIndex] = true;

        Intersection *intersection = findIntersection(u);
        if (!intersection)
            continue;

        Road *road = intersection->roads;
        while (road)
        {
            // Skip roads that are not "Clear" (status != 1)
            if (road->getStatus() != 1)
            {
                road = road->next;
                continue;
            }

            char v = road->dest;
            int weight = road->travelTime;
            int vIndex = v - 'A';

            if (dist[uIndex] != INT_MAX && dist[uIndex] + weight < dist[vIndex])
            {
                dist[vIndex] = dist[uIndex] + weight;
                parent[vIndex] = uIndex;
                pq.insert({dist[vIndex], v});
            }
            road = road->next;
        }
    }

    // Output the shortest path and its distance
    if (dist[endIndex] == INT_MAX)
    {
        std::cout << "No path found from " << start << " to " << end << "." << std::endl;
    }
    else
    {
        std::cout << "Shortest path from " << start << " to " << end << " is " << dist[endIndex] << "s." << std::endl;
        std::cout << "Path: ";
        char path[MAX_INTERSECTIONS];
        int pathLength = 0;
        int current = endIndex;

        while (current != -1)
        {
            path[pathLength++] = 'A' + current;
            current = parent[current];
        }

        for (int i = pathLength - 1; i >= 0; i--)
        {
            std::cout << path[i] << " ";
        }
        std::cout << std::endl;
    }
}

// Dijkstra's algorithm to find the next closest intersection
char Graph::dijkstra(char start, char end, unsigned int n)
{

    // n = 0 for considering all roads, n = 1 for considering only "Clear" roads
    int dist[MAX_INTERSECTIONS];
    int parent[MAX_INTERSECTIONS];
    bool visited[MAX_INTERSECTIONS];
    MinHeap<char>::Node node;
    MinHeap<char> pq(MAX_INTERSECTIONS);
    // Initialize arrays
    std::fill(dist, dist + MAX_INTERSECTIONS, INT_MAX);
    std::fill(visited, visited + MAX_INTERSECTIONS, false);
    std::fill(parent, parent + MAX_INTERSECTIONS, -1);

    int startIndex = start - 'A';
    int endIndex = end - 'A';

    dist[startIndex] = 0;

    pq.insert({0, start}); // Insert the source node into the priority queue

    while (!pq.isEmpty())
    {
        auto current = pq.extractMin();
        char u = current.data; // Intersection name
        int uIndex = u - 'A';

        if (visited[uIndex])
            continue; // Skip if already visited
        visited[uIndex] = true;

        Intersection *intersection = findIntersection(u);
        if (!intersection)
            continue;

        Road *road = intersection->roads;
        while (road)
        {
            // Skip roads that are not "Clear" (status != 1)
            if (road->getStatus() != 1 && n == 1)
            {
                road = road->next;
                continue;
            }

            char v = road->dest;
            int weight = road->travelTime;
            int vIndex = v - 'A';

            if (dist[uIndex] != INT_MAX && dist[uIndex] + weight < dist[vIndex])
            {
                dist[vIndex] = dist[uIndex] + weight;
                parent[vIndex] = uIndex;
                pq.insert({dist[vIndex], v});
            }
            road = road->next;
        }
    }

    if (dist[endIndex] == INT_MAX)
    {
        std::cout << "No path found from " << start << " to " << end << "." << std::endl;
        return '\0'; // Return null if no path is found
    }
    else
    {
        std::cout << "Shortest path from " << start << " to " << end << " is " << dist[endIndex] << "s." << std::endl;

        // Reconstruct the path from end to start using the parent array
        char path[MAX_INTERSECTIONS];
        int pathLength = 0;
        int current = endIndex;

        // Traverse the parent array to reconstruct the path
        while (current != -1)
        {
            path[pathLength++] = 'A' + current;
            current = parent[current];
        }

        // Ensure there is a valid path starting from 'start'
        if (pathLength < 2)
        {
            return '\0'; // Return '\0' if the path doesn't have a next node
        }

        // The immediate next node is the second node in the reconstructed path
        return path[pathLength - 2]; // Return the node immediately after the 'start'
    }
}

// simulate road closures from a CSV file
bool Graph::simulateRoadClosure(const std::string &fileName)
{
    std::ifstream file(fileName);
    if (!file)
    {
        std::cout << "Error opening file!" << std::endl;
        return false;
    }

    std::string line;
    // intersection1,intersection2,status
    // B,C,Blocked
    while (getline(file, line))
    {
        char start, end;
        char statusBuffer[100];
        if (sscanf(line.c_str(), "%c,%c,%s", &start, &end, statusBuffer) == 3)
        {
            std::string status = statusBuffer;
            updateRoadStatus(start, end, status);
        }
    }
    file.close();
    return true;
}

// update the status of a road between two intersections
void Graph::updateRoadStatus(char start, char end, std::string status)
{
    Intersection *startIntersection = findIntersection(start);

    // if the starting intersection is not found
    if (startIntersection == NULL)
        std::cout << "Intersection " << start << " not found.\n";

    else
    {
        Road *temp = startIntersection->roads;

        // iterate to end of the list if necessary
        while (temp != NULL)
        {
            // if the destination is the same then we assign new status
            if (temp->dest == end)
            {

                if (status == "Clear")
                {
                    temp->status = 1;
                    // std::cout << "Status for " << start << " -> " << end << " = Clear\n";
                }

                else if (status == "Blocked")
                {
                    temp->status = 2;
                    // std::cout << "Status for " << start << " -> " << end << " = Blocked\n";
                }

                else if (status == "Under")
                {
                    temp->status = 3;
                    // std::cout << "Status for " << start << " -> " << end << " = Under Repair\n";
                }
                return;
            }
            temp = temp->next;
        }
    }
}

// move selected vehicle to next closest intersection
/*Example: V1 is moving from A to E and next closest intersection is B, move to B*/
void Graph::moveVehiclesEfficiently(const std::string &vehicleName)
{
    Vehicle *vehicle = nullptr;
    for (int i = 0; i < MAX_INTERSECTIONS; i++)
    {
        if (intersections[i])
        {
            Vehicle *temp = intersections[i]->vehicles;
            while (temp)
            {
                if (temp->name == vehicleName)
                {
                    vehicle = temp;
                    break;
                }
                temp = temp->next;
            }
        }
    }
    if (vehicle == nullptr)
    {
        std::cout << "Vehicle is null" << std::endl;
        return;
    }

    char nextIntersection = dijkstra(vehicle->current, vehicle->end, 1);

    // if dijkstra returns an invalid intersection, handle it
    if (nextIntersection == '\0')
    {
        std::cout << "Error: Invalid intersection returned by Dijkstra's algorithm." << std::endl;
        return;
    }

    vehicle->printCurrent();
    vehicle->current = nextIntersection;
    vehicle->printCurrent();
    std::cout << "Vehicle " << vehicle->name << " moved to intersection " << vehicle->current << std::endl;
}

// Rerouting blocked or roads under repair
void Graph::rerouteForBlocked(char start, char end)
{
    Intersection *startIntersection = findIntersection(start);

    if (startIntersection == NULL)
    {
        std::cout << "Intersection " << start << " not found.\n";
        return;
    }

    else
    {
        Road *temp = startIntersection->roads;
        while (temp != NULL)
        {
            // std::cout<<"\nERROR FOUND.\n";
            if (temp->dest == end)
            {
                if (temp->status == 2 || temp->status == 3)
                { // checks only for blocked or under repair
                    // std::cout << "Road blocked " << start << " -> " << end << ". Rerouting...\n";
                    BFS(start, end);
                    return;
                }
            }
            temp = temp->next;
        }
    }
    std::cout << "Road Clear for " << start << " -> " << end << std::endl;
}

// Algorithm used for rerouting
void Graph::BFS(char start, char end)
{
    bool visited[MAX_INTERSECTIONS] = {false};
    int parent[MAX_INTERSECTIONS]; // for path reconstruction
    std::fill(parent, parent + MAX_INTERSECTIONS, -1);

    Queue queue; // BFS queue

    Intersection *startIntersection = findIntersection(start);
    if (!startIntersection)
    {
        std::cout << "Intersection " << start << " not found.\n";
        return;
    }

    // enqueue the starting intersection
    queue.enqueue(startIntersection);
    visited[start - 'A'] = true;

    // BFS Traversal
    while (queue.getPointers(1) != nullptr)
    {
        Intersection *current = queue.dequeue();
        char currentName = current->name;

        // if the destination is reached
        if (currentName == end)
        {
            std::cout << "Alternate route found: ";
            printReroutedPath(parent, start - 'A', end - 'A');
            std::cout << "\n\n";
            return;
        }

        // explore adjacent roads
        Road *road = current->roads;
        while (road)
        {
            int nextIndex = road->dest - 'A';

            if (!visited[nextIndex] && road->status == 1) // only visit 'Clear' roads
            {
                visited[nextIndex] = true;
                parent[nextIndex] = currentName - 'A';
                queue.enqueue(findIntersection(road->dest));
            }
            road = road->next;
        }
    }

    std::cout << "No alternate route found from " << start << " to " << end << "." << std::endl
              << std::endl;
}

// Checking the whole traffic network for blocked/repairing roads and rerouting
void Graph::rerouteNetwork()
{
    // Iterate through all intersections
    for (int i = 0; i < MAX_INTERSECTIONS; ++i)
    {
        if (intersections[i])
        { // Ensure the intersection is valid
            Road *road = intersections[i]->roads;

            // Iterate through each road connected to the intersection
            while (road)
            {
                // If the road is blocked (status 2) or under repair (status 3), reroute traffic
                if (road->status == 2 || road->status == 3)
                {
                    std::cout << "Rerouting required for road "
                              << intersections[i]->name << " -> "
                              << road->dest << "..." << std::endl;

                    // Call rerouting logic for blocked or under repair roads
                    rerouteForBlocked(intersections[i]->name, road->dest);
                }
                road = road->next; // Move to the next road
            }
        }
    }
}

// After calling blockRoad function also call rerouteNetwork to update the network
void Graph::blockRoad(char start, char end)
{
    Intersection *startIntersection = findIntersection(start);

    // if the starting intersection is not found
    if (startIntersection == NULL)
        std::cout << "Intersection " << start << " not found.\n";

    else
    {
        Road *temp = startIntersection->roads;

        // iterate to end of the list if necessary
        while (temp != NULL)
        {
            // if the destination is the same then we assign new status
            if (temp->dest == end)
            {
                temp->status = 2;
                return;
            }
            temp = temp->next;
        }
    }
    std::cout << "No direct Road found between " << start << " -> " << end << ".\n\n";
}

// Print the rerouted path
void Graph::printReroutedPath(int parent[], int startIndex, int endIndex)
{
    if (endIndex == -1 || startIndex == endIndex)
    {
        std::cout << char('A' + startIndex) << " ";
        return;
    }

    printReroutedPath(parent, startIndex, parent[endIndex]);
    std::cout << char('A' + endIndex) << " ";
}

// Print all Blocked roads
void Graph::printBlockedRoads()
{
    bool flag = false;
    for (int i = 0; i < MAX_INTERSECTIONS; ++i)
    {
        if (intersections[i])
        {
            Road *road = intersections[i]->roads;
            while (road)
            {
                if (road->status == 2 || road->status == 3)
                {
                    std::cout << intersections[i]->name << " to " << road->dest << " is blocked.\n";
                    flag = true;
                }
                road = road->next;
            }
        }
    }
    if (!flag)
    {
        std::cout << "No blocked roads found.\n";
    }
    std::cout << std::endl;
}

// Helper function for Depth-First Search (DFS) without STL
void Graph::dfs(Intersection *current, char end, char currentPath[], int pathIndex, bool visited[], char allPaths[][100], int &pathCount)
{
    // Mark the current intersection as visited
    visited[current->name - 'A'] = true;

    // Add the current intersection to the path
    currentPath[pathIndex] = current->name;
    pathIndex++;

    // If the destination is reached, store the path
    if (current->name == end)
    {
        // Save the current path to allPaths
        for (int i = 0; i < pathIndex; i++)
        {
            allPaths[pathCount][i] = currentPath[i];
        }
        allPaths[pathCount][pathIndex] = '\0'; // Null-terminate the path
        pathCount++;
    }
    else
    {
        // Explore all connected roads (adjacent intersections)
        Road *road = current->roads;
        while (road)
        {
            Intersection *nextIntersection = findIntersection(road->dest);

            // If not visited, continue DFS
            if (!visited[nextIntersection->name - 'A'])
            {
                dfs(nextIntersection, end, currentPath, pathIndex, visited, allPaths, pathCount);
            }
            road = road->next; // Move to the next connected road
        }
    }

    // Backtrack: Unmark the current intersection as visited
    visited[current->name - 'A'] = false;
}

// Function to find and display all routes between two intersections
void Graph::findAllRoutes(char start, char end)
{
    Intersection *startIntersection = findIntersection(start);

    // Error handling: Check if the start or end intersections exist
    if (!startIntersection)
    {
        cout << "Start intersection " << start << " not found.\n";
        return;
    }
    if (!findIntersection(end))
    {
        cout << "End intersection " << end << " not found.\n";
        return;
    }

    // Variables for DFS
    char currentPath[100];                     // Array to store the current path
    char allPaths[100][100];                   // Array to store all paths
    bool visited[MAX_INTERSECTIONS] = {false}; // Visited array
    int pathCount = 0;                         // Count of paths found
    int pathIndex = 0;                         // Current index in the path

    // Start DFS from the starting intersection
    dfs(startIntersection, end, currentPath, pathIndex, visited, allPaths, pathCount);

    // Display all paths
    if (pathCount == 0)
    {
        cout << "No routes found from " << start << " to " << end << ".\n";
    }
    else
    {
        cout << "All routes from " << start << " to " << end << ":\n";
        for (int i = 0; i < pathCount; i++)
        {
            for (int j = 0; allPaths[i][j] != '\0'; j++)
            {
                cout << allPaths[i][j];
                if (allPaths[i][j + 1] != '\0')
                    cout << " -> ";
            }
            cout << endl;
        }
    }
}

void Graph::moveVehicleToNewIntersection(const std::string &vehicleName, char newIntersection)
{
    Vehicle *vehicle = nullptr;
    Intersection *currentIntersection = nullptr;
    Intersection *prevIntersection = nullptr;
    // search for the vehicle across all intersections
    for (int i = 0; i < MAX_INTERSECTIONS; i++)
    {
        if (intersections[i])
        {
            Vehicle *temp = intersections[i]->vehicles;
            while (temp)
            {
                if (temp->name == vehicleName)
                {
                    vehicle = temp;
                    currentIntersection = intersections[i]; // store the current intersection
                    break;
                }
                temp = temp->next;
            }
        }
        if (vehicle)
            break; // exit outer loop if vehicle is found
    }

    // if the vehicle is not found, print an error and exit
    if (!vehicle)
    {
        std::cout << "Vehicle " << vehicleName << " not found." << std::endl;
        return;
    }

    // check if there is a direct road from current intersection to the new intersection
    Road *road = currentIntersection->roads;
    bool roadFound = false;
    while (road)
    {
        if (road->dest == newIntersection && road->getStatus() == 1)
        { // check if road is clear
            roadFound = true;
            break;
        }
        road = road->next;
    }

    // if a direct road exists, move the vehicle
    if (roadFound)
    {
        vehicle->printCurrent();                         // print current position
        vehicle->current = newIntersection;              // move vehicle to the new intersection
        currentIntersection->incrementCongestionLevel(); // increase congestion at new intersection
        vehicle->printCurrent();                         // print new position
        std::cout << "Vehicle " << vehicle->name << " moved to intersection " << vehicle->current << std::endl;
    }
    else
    {
        std::cout << "No direct road or blocked road found from " << currentIntersection->name << " to " << newIntersection << "." << std::endl;
    }
}

//Function to find the optimal path using A* Algorithm
void Graph::aStar(char start, char end)
{
    int dist[MAX_INTERSECTIONS];       // distance from source
    int parent[MAX_INTERSECTIONS];     // path reconstruction
    bool visited[MAX_INTERSECTIONS];   // visited array
    MinHeap<char>::Node node;          // MinHeap Node structure
    MinHeap<char> pq(MAX_INTERSECTIONS); 

    std::fill(dist, dist + MAX_INTERSECTIONS, INT_MAX);     
    std::fill(visited, visited + MAX_INTERSECTIONS, false); 
    std::fill(parent, parent + MAX_INTERSECTIONS, -1);      

    int startIndex = start - 'A';
    int endIndex = end - 'A';

    dist[startIndex] = 0;
    pq.insert({0, start}); 

    auto heuristic = [](char current, char target) {
        return abs(current - target);  // Manhattan-like heuristic
    };

    while (!pq.isEmpty())
    {
        auto current = pq.extractMin();
        char u = current.data;
        int uIndex = u - 'A';

        if (visited[uIndex]) continue;
        visited[uIndex] = true;

        if (u == end) break; // Reached destination

        Intersection *intersection = findIntersection(u);
        if (!intersection) continue;

        Road *road = intersection->roads;
        while (road)
        {
            if (road->getStatus() != 1) 
            {
                road = road->next;
                continue;
            }

            char v = road->dest;
            int vIndex = v - 'A';
            int weight = road->travelTime;

            int tentativeDist = dist[uIndex] + weight;
            int totalCost = tentativeDist + heuristic(v, end);

            if (tentativeDist < dist[vIndex])
            {
                dist[vIndex] = tentativeDist;
                parent[vIndex] = uIndex;
                pq.insert({totalCost, v});
            }
            road = road->next;
        }
    }

    if (dist[endIndex] == INT_MAX)
    {
        std::cout << "No path found from " << start << " to " << end << "." << std::endl;
    }
    else
    {
        std::cout << "Fastest path from " << start << " to " << end << " is " << dist[endIndex] << "s." << std::endl;
        std::cout << "Path: ";
        char path[MAX_INTERSECTIONS];
        int pathLength = 0;
        int current = endIndex;

        while (current != -1)
        {
            path[pathLength++] = 'A' + current;
            current = parent[current];
        }

        for (int i = pathLength - 1; i >= 0; i--)
        {
            std::cout << path[i] << " ";
        }
        std::cout << std::endl;
    }
}
