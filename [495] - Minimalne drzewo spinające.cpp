/*

Copyright (C) Pawel Masluch, 2021. All rights reserved.

Algorytm Prima do wyznaczenia minimalnego drzewa rozpinajacego dla spojnego(!) grafu nieskierowanego G.
W rozwiazaniu wyznaczam jedynie koszt takiego minimalnego drzewa. 

*/

#include<cstdio>
#include<queue>
#include<vector>


using namespace std;


typedef long long LL;

typedef pair < LL, LL > PLL;

typedef vector < PLL > VPLL;

typedef priority_queue < PLL > PQ_PLL;


#define REP(i,a,b) for(LL i=a; i<=b; ++i)

#define MP make_pair

#define ST first

#define ND second

#define PB push_back

#define S size

#define P push

#define p pop

#define T top

#define E empty 


const LL MAX_N = 1000000, INF = (LL)1000000199 * 1000000099;


PQ_PLL PQ;

VPLL G[MAX_N];

bool odw[MAX_N]; // czy wierzcholek jest w MST

LL n, m, best[MAX_N]; // best[u] - najtansza krawedz z MST do wierzcholka 'u'


void wczytaj()
{
	scanf( "%lld %lld", &n, &m );
	
	LL u, v, w;
	
	REP(i,1,m)
	{
		scanf( "%lld %lld %lld", &u, &v, &w );
		
		--u;    --v;
		
		G[u].PB( MP( w, v ) );
		
		G[v].PB( MP( w, u ) );
	}
}


void inicjuj()
{
	REP(u,0,n-1)
	{
		best[u] = INF;
	}
}


void Prim(int x)
{
	LL wyn = 0, u, v, w, r;
	
	best[x] = 0; // za dojscie do wierzcholka "x" z pustego MST nie ponosimy zadnego kosztu 
	
	PQ.P( MP( -best[x], x ) );
	
	while( !PQ.E() )
	{
		w = -PQ.T().ST;    u = PQ.T().ND;
		
		PQ.p();
		
		if( !odw[u] ) // jesli wczesniej nie rozwazano tego wierzcholka
		{
			wyn += w;
			
			r = G[u].S();
			
			REP(i,0,r-1)
			{
				w = G[u][i].ST;    v = G[u][i].ND;
				
				if( !odw[v] ) // jesli wczesniej nie rozwazano tego wierzcholka
				{
					if( w < best[v] )
					{
						best[v] = w;
						
						PQ.P( MP( -best[v], v ) );
					}
				}
			}
			
			odw[u] = true;	
		}
	}
	
	printf( "%lld\n", wyn );
}


void oblicz()
{
	Prim( 0 );
}


void solve()
{
	wczytaj();
	
	inicjuj();
	
	oblicz();
}


int main()
{
	solve();
	
	return 0;
}
