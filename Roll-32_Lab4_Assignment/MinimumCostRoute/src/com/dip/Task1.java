package com.dip;

import java.sql.SQLOutput;
import java.util.*;
import java.util.Scanner;


class Graph {
    final Integer inf = Integer.MAX_VALUE;
    int numOfVertices;
    ArrayList<ArrayList<Pair>> adj = new ArrayList<ArrayList<Pair>>();

    Graph(int numOfVertices){
        this.numOfVertices = numOfVertices;
        for(int i = 0; i < numOfVertices; i++){
            adj.add(new ArrayList<Pair>());
        }
    }

    public void addEdge(int u, int v, int w){
        adj.get(u).add(new Pair(v, w));
        adj.get(v).add(new Pair(u, w));
    }

    void bfs(int src){
        boolean visited[] = new boolean[numOfVertices];
        LinkedList<Integer> q = new LinkedList<Integer>();
        ArrayList<Integer> dist = new ArrayList<Integer>(Collections.nCopies(numOfVertices, inf));
        visited[src] = true;
        System.out.println("BFS:");
        dist.set(src, 0);
        q.add(src);
        while(q.size() != 0){
            int u = q.poll();
            System.out.printf("%d ", u);
            for(Pair p: adj.get(u)){
                int v = p.destination;
                int w = p.weight;
                if(!visited[v]){
                    dist.set(v, dist.get(u)+1);
                    q.add(v);
                    visited[v] = true;
                }
            }
        }
        System.out.printf("\n");
        System.out.println("Shortest route using bfs: " + dist.get(13));
    }

    void dijkstraShortestPath(int src){
        PriorityQueue<Node> pq = new PriorityQueue<>(numOfVertices, new Node());
        ArrayList<Integer> dist = new ArrayList<Integer>(Collections.nCopies(numOfVertices, inf));
        ArrayList<Integer> pi = new ArrayList<Integer>(Collections.nCopies(numOfVertices, -1));
        dist.set(src, 0);
        pq.add(new Node(src, 0));
        while(!pq.isEmpty()){
            int u = pq.peek().node;
            pq.remove();
            if(u == inf){
                break;
            }
            for(Pair itr : adj.get(u)){
                int v = itr.destination;
                int w = itr.weight;
                if(dist.get(v) > dist.get(u) + w){
                    dist.set(v, dist.get(u) + w);
                    pq.add(new Node(v, dist.get(v)));
                    pi.set(v, u);
                }
            }
        }

        int k = 13;
        ArrayList<Integer> path = new ArrayList<Integer>();
        while(k != -1){
            path.add(k);
            k = pi.get(k);
        }
        Collections.reverse(path);
        System.out.printf("Shortest route: ");
        for(int i : path){
            if(i == 13){
                System.out.printf("Moghbazar.\n");
            }
            else if(i == 0){
                System.out.printf("Motijheel -> ");
            }
            else{
                System.out.printf("%c -> ", i + 64);
            }
        }
        System.out.println("Shortest route traffic from Motijheel to Moghbazar: " + dist.get(13).toString());
    }

}


class Node implements Comparator<Node>
{
    public int node;
    public int cost;

    public Node()
    {
    }

    public Node(int node, int cost)
    {
        this.node = node;
        this.cost = cost;
    }

    @Override
    public int compare(Node node1, Node node2)
    {
        if (node1.cost < node2.cost)
            return -1;
        if (node1.cost > node2.cost)
            return 1;
        return 0;
    }
}

class Pair{
    int destination, weight;
    public Pair(int destination, int weight){
        this.destination = destination;
        this.weight = weight;
    }
    @Override
    public String toString(){
        return "Destination: " + String.valueOf(destination) + ". Weight: " + String.valueOf(weight) + ".";
    }
}

public class Task1 {

    public static void main(String[] args) {
        Graph g = new Graph(14);
        // Edges in the given graph:
        g.addEdge(0, 1, 4);
        g.addEdge(1, 2, 3);
        g.addEdge(1, 8, 2);
        g.addEdge(2, 7, 6);
        g.addEdge(8, 9, 7);
        g.addEdge(2, 3, 5);
        g.addEdge(3, 6, 3);
        g.addEdge(3, 4, 7);
        g.addEdge(4, 5, 2);
        g.addEdge(6, 7, 1);
        g.addEdge(6, 13, 3);
        g.addEdge(7, 8, 4);
        g.addEdge(7, 10, 7);
        g.addEdge(9, 10, 1);
        g.addEdge(10, 11, 4);
        g.addEdge(11, 12, 6);
        g.addEdge(11, 13, 7);
        g.addEdge(12, 13, 2);
        g.dijkstraShortestPath(0);
    }
}
