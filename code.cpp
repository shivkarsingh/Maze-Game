#include<bits/stdc++.h>
using namespace std;


int dx[4] = { 1, 0, -1, 0 };
int dy[4] = { 0, 1, 0, -1 };

void print( vector<vector<double>> arr ){

    for( int i = 0; i < arr.size(); i++ ){
        for( int j = 0; j < arr[0].size(); j++ ){
            cout << arr[i][j] << " ";
        } 
        cout<<endl;
    }
}


double bellman ( double r, double df, double v ) {

    return r + ( df * v );

}


void assignvalue ( vector<vector<int>> &grid, vector<vector<double>> &bv,
 vector<vector<bool>> &vis, double r, double df, double v, pair< int, int > fp, int row, int col ){

    queue<pair<pair<int,int>,double>> q;

    q.push({{ fp.first, fp.second }, v });
    vis[fp.first][fp.second] = 1;

    while( !q.empty() ){

        auto coord = q.front().first;
        double val = q.front().second;

        q.pop();

        if( !((coord.first == fp.first) && (coord.second == fp.second ))){

            bv[coord.first][coord.second] = bellman ( r, df, val );

        }

        else{

            bv[coord.first][coord.second] = val;

        }

        for( int k = 0; k < 4; k++ ){

            int nr = coord.first + dy[k];
            int nc = coord.second + dx[k]; 

            if( nr >= 0 && nc >= 0 && nr < row && nc < col ){

                if( grid[nr][nc] == 0 && vis[nr][nc] == 0 ){

                    vis[nr][nc] = 1;
                    q.push({ { nr, nc },  bv[coord.first][coord.second] });

                }
            }
        }

    }
}

    void dijkstra(vector<vector<int>>& grid, vector<vector<double>> &bv, pair<int,int> sp, 
        pair<int,int> fp, int row, int col, vector<pair<int,int>> & path, vector<vector<double>> &dist ) {

        priority_queue<pair<double,pair<int,int>>,vector<pair<double,pair<int,int>>>,greater<pair<double,pair<int,int>>>> pq;

        vector<vector<pair<int, int>>> parent(row, vector<pair<int, int>>(col));

        for(int i=0;i<row;i++){
            for(int j=0;j<col;j++){
                parent[i][j] = {i,j};
            }
        }


        dist[sp.first][sp.second] = 0 ;
        pq.push({0,{sp.first,sp.second}});

        while(!pq.empty()){

            int i = pq.top().second.first;
            int j = pq.top().second.second;
            double d = pq.top().first;

            if( (i == fp.first ) && ( j == fp.second ) ) { break; }

            pq.pop();

            for(int k=0;k<4;k++){

                int ni = i + dy[k];
                int nj = j + dx[k];

                if( ni>=0 && ni<row && nj>=0 && nj<col && grid[ni][nj] == 0){

                    if( d +  bv[ni][nj] < dist[ni][nj] ){

                        dist[ni][nj] = d +  bv[ni][nj] ;
                        pq.push({dist[ni][nj],{ni,nj}});
                        parent[ni][nj] = {i,j};

                    }

                }
            }
        }

        
        
        int x = fp.first, y = fp.second;

        while (!(parent[x][y].first == x && parent[x][y].second == y)) {

            path.push_back({x, y});

            auto p = parent[x][y];
            x = p.first;
            y = p.second;

        }

        path.push_back({sp.first, sp.second}); 
        reverse(path.begin(), path.end());

    }


int main (){

    int row, col;

    cout << " Enter size of grid : "<< endl;
    cin >> row >> col;

    double df;
    double r;

    cout << " Enter discount factor : "<<endl;
    cin >> df;

    cout << " Enter living penalty : "<<endl;
    cin >> r;

    vector<vector<int>> grid( row, vector<int> (col));
    vector<vector<double>> bv( row, vector<double>(col));

    cout << "Enter coordinates for obstacles ( to exit enter -1 -1 ) : "<<endl;

    

    while ( true ){

        int rw,co;

        cin >> rw >> co;

        if( rw == -1 ){ break; }

        grid[rw][co] = 1;

    }

    cout << "Enter coordinates for danger ( to exit enter -1 -1 ) : "<<endl;

       while ( true ){

        int rw,co;

        cin >> rw >> co;

        if( rw == -1 ){ break; }

        grid[rw][co] = -1;

    }

    cout<<endl<<endl;

    for( int i = 0; i < grid.size(); i++ ){
        for( int j = 0; j < grid[0].size(); j++ ){
            cout << grid[i][j] << " ";
        } 
        cout<<endl;
    }

    cout<<endl;

    cout << "Enter coordinates for start point : "<<endl;

    pair< int, int > sp;
    pair< int, int > fp;

    cin >> sp.first >> sp.second;

    cout << "Enter coordinates for end point : "<<endl;

    cin >> fp.first >> fp.second;

    double value = max( row, col );

    vector<vector<bool>> vis( row, vector<bool>(col));

    assignvalue( grid, bv, vis, r, df, value, fp, row, col );

    cout<<endl<<endl;

    for( int i = 0; i < bv.size(); i++ ){
        for( int j = 0; j < bv[0].size(); j++ ){
            cout << bv[i][j] << " ";
        } 
        cout<<endl;
    }



    vector<pair<int,int>> path;
    vector<vector<double>> dist(row,vector<double>(col,1e5));

    dijkstra( grid, bv, sp, fp, row, col, path, dist );

    cout<<endl<<endl;

    for( int i = 0; i < path.size(); i++ ){
        cout<<'('<<path[i].first<<" , "<<path[i].second<<')'<<"  ";
    }

    cout << endl<<endl;

    for( int i = 0; i < dist.size(); i++ ){
        for( int j = 0; j < dist[0].size(); j++ ){
            if( dist[i][j] == 1e5 ) dist[i][j] = 0;
            cout << dist[i][j] << " ";
        } 
        cout<<endl;
    }


}