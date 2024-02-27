#include<fstream>

#include<iostream>

using namespace std;

struct edge {struct vertex * Vertex; int weight; edge * nextedge;

    edge(edge * e = 0, struct vertex * v = 0, int w = 0)

    { Vertex = v; weight = w; nextedge = e;}

};



struct vertex {char name; vertex * nextvertex ; edge * edgelist;

    int index; bool final; vertex * pre;

    vertex(char n = '\0', vertex * v = 0)

    {name = n; nextvertex = v; edgelist = 0;

        index = -1; final = false; pre = 0;}

};



int main(){

    char input_file[128]; // streamed input file

    cout << "In what file is the data for the graph contained?\n> ";

    cin.getline(input_file, 128);

    ifstream infile( input_file );

    vertex * graph = 0; // start reference to graph structure

    vertex * startptr = 0, * finishptr = 0; // pointers for incoming vertex info

    vertex * vertexsearch = 0, * vptr = 0;

    vertex * last;

    vertex * w;

    edge * edgeptr = 0;

    int weight;

    char start, finish, comma; // variables to store input, i.e. tuple of (a,b,1) (start comma finish comma weight)

    bool startnotfound = true, finishnotfound = true;

    while( !infile.eof() ){

        infile >> start >>comma >> finish >> comma >> weight;



        startptr = 0; // reset start vertex reference to null for new incoming start char

        vertexsearch = graph; // reset vertex searcher to beginning of graph



        while (vertexsearch != 0) { // search for match for incoming start vertex

            if (vertexsearch->name == start) {

                startnotfound = false;

                startptr = vertexsearch;

                break;

            }



            else {

                startnotfound = true;

                vertexsearch = vertexsearch->nextvertex;

            }

        }



        if (startnotfound) { // if not found, create it

            startptr = new vertex(start);



            if (last != 0) {

                last->nextvertex = startptr;

            }



            last = startptr; // last points to newly added vertex at end of list



            if (graph == 0) { // if graph is empty, initialize it

                graph = startptr;

            }

        }



        finishptr = 0; // reset finish vertex reference to null for new incoming finish char

        vertexsearch = graph; // reset vertex searcher to beginning of graph



        while (vertexsearch != 0) { // search for match for incoming finish vertex

            if (vertexsearch->name == finish) {

                finishnotfound = false;

                finishptr = vertexsearch;

                break;

            }



            else {

                finishnotfound = true;

                vertexsearch = vertexsearch->nextvertex;

            }

        }



        if (finishnotfound) { // if not found, create it

            finishptr = new vertex(finish);



            last->nextvertex = finishptr;

            last = finishptr; // last points to newly added vertex at end of list

        }



        edge * newEdge = new edge(0, finishptr, weight); // create edge from start to finish

        edgeptr = startptr->edgelist;



        if (edgeptr == 0) {

            startptr->edgelist = newEdge;

        }



        else {

            while (edgeptr->nextedge != 0) {

                edgeptr = edgeptr->nextedge;

            }



            edgeptr->nextedge = newEdge;

        }

    }



    // Output the graph

    vptr = graph;

    while( vptr ){

        cout << vptr->name << '\n';

        edgeptr = vptr->edgelist;

        while( edgeptr ){

            cout << "     Edge to " << edgeptr->Vertex->name

                 << " with weight " << edgeptr->weight << '\n';

            edgeptr = edgeptr->nextedge;

        }

        vptr = vptr->nextvertex;

    }

    // From where to where

    cout << "From where: ";

    cin >> start;

    cout <<"to where: ";

    cin >> finish;

    vertex * s = graph;

    startptr = finishptr = 0;

    while( s ){

        if( s->name == start ){

            startptr = s;

        }

        if (s->name == finish ){

            finishptr = s;

        }

        s->index = INT_MAX;

        s->final = false;

        s = s->nextvertex;

    }

    if( !startptr ){

        cout << "Start point given is not a valid vertex.\n";

        return 1;

    }

    if( !finishptr ){

        cout << "Finish point given is not a valid vertex.\n";

        return 1; }

    last = startptr;

    last->index = 0;

    last->final = true;

    while( !(finishptr->final) ){

        edgeptr = last->edgelist;



        while (edgeptr != 0) {

            vertexsearch = edgeptr->Vertex;

            if (!vertexsearch->final && vertexsearch->index > last->index + edgeptr->weight) {

                vertexsearch->index = last->index + edgeptr->weight;

                vertexsearch->pre = last;

            }



            edgeptr = edgeptr->nextedge;

        }



        w = 0;

        vertexsearch = graph;

        int smallestWeight = INT_MAX;



        while (vertexsearch != 0) {

            if (!vertexsearch->final && vertexsearch->index < smallestWeight) {

                smallestWeight = vertexsearch->index;

                w = vertexsearch;

            }



            vertexsearch = vertexsearch->nextvertex;

        }



        if (w != 0) {

            w->final = true;

            last = w;

        }



        else {

            break;

        }

    }

    vptr = finishptr;

    if ( vptr->pre )

        while( vptr ){

            cout << vptr->name << '\n';

            vptr = vptr->pre;

        } else

        cout << "No such path.\n";

    return 0;

}