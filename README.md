# Stock_Market_Simulator

# **Stock Market Simulation in C++** 🚀

This project simulates a **Stock Market Order Matching System** with **Multi-threading**, **Priority Queues**, and **Graph Algorithms** for **Market Analysis**.

---

## **Features**
✅ **Multi-threaded Order Matching** using **mutex and priority queues**  
✅ **Buy & Sell Order Processing** with **Heap-based optimization**  
✅ **Graph-based Market Network Analysis**  
✅ **Dijkstra's Algorithm for finding Minimum Transaction Fees**  
✅ **Graphviz Integration for Market Visualization**  

---

## **1️⃣ Order Matching System**
### **1.1 Order Structure**
- Each order contains:
  - **ID**: Unique identifier
  - **Type**: `"buy"` or `"sell"`
  - **Price**: Order price
  - **Quantity**: Number of shares

### **1.2 Order Queues**
- **Buy Orders (Max-Heap)** → Highest price first
- **Sell Orders (Min-Heap)** → Lowest price first

### **1.3 Order Execution (Multi-threaded)**
- Orders are **executed if the highest buy price is greater than or equal to the lowest sell price**.

---

## **2️⃣ Market Network Graph**
### **2.1 Market Connections**
- Each market is represented as a **node** in a graph.
- **Edges** represent **transaction fees** between markets.

### **2.2 Displaying Market Network**
- Shows all markets and their transaction fees.

---

## **3️⃣ Dijkstra’s Algorithm (Finding Cheapest Route)**
- Finds the **minimum transaction fee path** between markets.

---

## **4️⃣ Graph Visualization with Graphviz**
- Generates a **Graphviz DOT file** for market visualization.
- **Run Graphviz Command to Generate Image:**
```bash
dot -Tpng market_graph.dot -o market_graph.png
```

---

## **5️⃣ Main Function (Workflow)**
- Starts **order processing in a separate thread**.
- Adds **buy/sell orders**.
- Stores orders in a file.
- Defines **market connections**.
- Runs **Dijkstra's Algorithm** to find the cheapest transaction route.
- Generates **Graphviz visualization**.

---

## **💡 How to Run**
### **1️⃣ Compile and Run the Code**
```bash
g++ stock_market_sim.cpp -o stock_market_sim -lpthread
./stock_market_sim
```

### **2️⃣ Generate Market Graph Image**
```bash
dot -Tpng market_graph.dot -o market_graph.png
```

---

## **🛠️ Future Improvements**
🚀 **Implement AVL Tree for Order Book** – Faster lookup  
🚀 **Integrate Real-time Stock Data API** – Simulate real trades  
🚀 **GUI for Visualization** – Interactive stock market interface  

---

## **🐝 Conclusion**
This **C++ Stock Market Simulation** provides a **realistic order matching system**, uses **graph algorithms** for **market optimization**, and supports **Graphviz visualization**. 💹

