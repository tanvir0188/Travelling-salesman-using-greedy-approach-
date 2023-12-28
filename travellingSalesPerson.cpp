#include <iostream>
#include <vector>
#include <climits>

using namespace std;

pair<int, vector<int>> tspGreedy(int startCity, int n, vector<vector<int>> &distancesMatrix)
{
    vector<bool> visited(n, false);
    visited[startCity] = true;

    int cost = 0;
    int currentCity = startCity;
    vector<int> visitedCities = {startCity};

    while (visitedCities.size() < n)
    {
        int nextCity = -1;
        int minDistance = INT_MAX;

        for (int i = 0; i < n; ++i)
        {
            if (!visited[i] && distancesMatrix[currentCity][i] != -1 && distancesMatrix[currentCity][i] < minDistance)
            {
                minDistance = distancesMatrix[currentCity][i];
                nextCity = i;
            }
        }

        if (nextCity == -1)
        {
            cout << "Error: Unable to find the next city.\n";
            return make_pair(-1, vector<int>());
        }

        visitedCities.push_back(nextCity);
        visited[nextCity] = true;
        cost += minDistance;
        currentCity = nextCity;
    }

    cost += distancesMatrix[currentCity][startCity];
    visitedCities.push_back(startCity);

    return make_pair(cost, visitedCities);
}

int main()
{
    int n;

    cout << "Enter the number of cities: ";
    cin >> n;

    if (n <= 0)
    {
        cout << "Error: Number of cities must be greater than 0.\n";
        return 1;
    }

    vector<vector<int>> distancesMatrix(n, vector<int>(n, 0));

    cout << "Enter the distance matrix for the cities:\n";
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cin >> distancesMatrix[i][j];
            if (distancesMatrix[i][j] < -1)
            {
                cout << "Error: Distances must be non-negative or -1 for missing edges.\n";
                return 1;
            }
        }
    }

    int startCity;
    cout << "Enter the starting city (0 to " << n - 1 << "): ";
    cin >> startCity;

    if (startCity < 0 || startCity >= n)
    {
        cout << "Error: Invalid starting city.\n";
        return 1;
    }

    pair<int, vector<int>> result = tspGreedy(startCity, n, distancesMatrix);

    int minDistance = result.first;
    vector<int> visitedCities = result.second;

    if (minDistance == -1)
    {
        cout << "Unable to find a valid tour.\n";
    }
    else
    {
        cout << "Minimum Distance: " << minDistance << endl;
        cout << "Visited Cities: ";
        for (int i = 0; i < visitedCities.size(); ++i)
        {
            cout << visitedCities[i] << " ";
        }
        cout << endl;
    }

    return 0;
}
