#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <thread>
#include <mutex>
#include <limits>
using namespace std;

mutex orderMutex; // For multi-threaded order processing

// Stock Order Structure
struct Order {
    int id;
    string type; // "buy" or "sell"
    double price;
    int quantity;
    Order(int i, string t, double p, int q) : id(i), type(t), price(p), quantity(q) {}
};

// Max-Heap for Buy Orders, Min-Heap for Sell Orders
struct CompareBuy {
    bool operator()(Order const& o1, Order const& o2) {
        return o1.price < o2.price;
    }
};

struct CompareSell {
    bool operator()(Order const& o1, Order const& o2) {
        return o1.price > o2.price;
    }
};

priority_queue<Order, vector<Order>, CompareBuy> buyOrders;
priority_queue<Order, vector<Order>, CompareSell> sellOrders;

// Order Book (AVL Tree can be used for optimization)
unordered_map<int, Order> orderBook;

// Graph for Market Analysis (Adjacency List)
unordered_map<string, vector<pair<string, double>>> marketGraph;

void executeOrders() {
    while (!buyOrders.empty() && !sellOrders.empty()) {
        Order buy = buyOrders.top();
        Order sell = sellOrders.top();
        
        if (buy.price >= sell.price) {
            orderMutex.lock();
            cout << "Executing trade: Buy Order " << buy.id << " matched with Sell Order " << sell.id << endl;
            buyOrders.pop();
            sellOrders.pop();
            orderMutex.unlock();
        } else {
            break;
        }
    }
}

void addOrder(int id, string type, double price, int quantity) {
    orderMutex.lock();
    Order newOrder(id, type, price, quantity);
    orderBook[id] = newOrder;
    if (type == "buy")
        buyOrders.push(newOrder);
    else
        sellOrders.push(newOrder);
    orderMutex.unlock();
}

void saveOrdersToFile() {
    ofstream file("orders.txt");
    for (auto &pair : orderBook) {
        file << pair.second.id << " " << pair.second.type << " " << pair.second.price << " " << pair.second.quantity << "\n";
    }
    file.close();
}

void addMarketEdge(string market1, string market2, double transactionFee) {
    marketGraph[market1].push_back({market2, transactionFee});
    marketGraph[market2].push_back({market1, transactionFee});
}

void showMarketConnections() {
    for (auto &pair : marketGraph) {
        cout << "Market: " << pair.first << " connects to:\n";
        for (auto &neighbor : pair.second) {
            cout << " -> " << neighbor.first << " with fee " << neighbor.second << "\n";
        }
    }
}

// Dijkstra's Algorithm for Market Route Optimization
void dijkstra(string startMarket) {
    unordered_map<string, double> minCost;
    for (auto &pair : marketGraph) {
        minCost[pair.first] = numeric_limits<double>::max();
    }
    minCost[startMarket] = 0;
    
    priority_queue<pair<double, string>, vector<pair<double, string>>, greater<pair<double, string>>> pq;
    pq.push({0, startMarket});
    
    while (!pq.empty()) {
        auto [cost, market] = pq.top(); pq.pop();
        if (cost > minCost[market]) continue;
        
        for (auto &neighbor : marketGraph[market]) {
            double newCost = cost + neighbor.second;
            if (newCost < minCost[neighbor.first]) {
                minCost[neighbor.first] = newCost;
                pq.push({newCost, neighbor.first});
            }
        }
    }
    
    cout << "\nMinimum Transaction Fees from " << startMarket << " to other markets:\n";
    for (auto &pair : minCost) {
        cout << pair.first << " : " << (pair.second == numeric_limits<double>::max() ? -1 : pair.second) << "\n";
    }
}

// Generate Graphviz DOT file for visualization
void generateGraphvizFile() {
    ofstream file("market_graph.dot");
    file << "graph MarketGraph {\n";
    for (auto &pair : marketGraph) {
        for (auto &neighbor : pair.second) {
            file << "    \"" << pair.first << "\" -- \"" << neighbor.first << "\" [label=\"" << neighbor.second << "\"];\n";
        }
    }
    file << "}";
    file.close();
    cout << "\nGraphviz DOT file 'market_graph.dot' generated. Use 'dot -Tpng market_graph.dot -o market_graph.png' to visualize.\n";
}

int main() {
    thread orderThread(executeOrders);
    addOrder(1, "buy", 150.5, 10);
    addOrder(2, "sell", 148.0, 5);
    addOrder(3, "buy", 152.0, 20);
    addOrder(4, "sell", 151.0, 15);
    saveOrdersToFile();
    
    addMarketEdge("NYSE", "NASDAQ", 0.02);
    addMarketEdge("NASDAQ", "LSE", 0.03);
    addMarketEdge("NYSE", "LSE", 0.05);
    showMarketConnections();
    
    dijkstra("NYSE");
    
    generateGraphvizFile();
    
    orderThread.join();
    return 0;
}
