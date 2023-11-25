// Program Tugas Post Day Modul 2 Online Learning
// Varel Tiara - 19623183

#include <iostream>
#include <math.h>
#include <vector>
#include <fstream>

using namespace std;

float koor[2] = {0,0};
vector<vector<int>> history;
int n = 0;

void lokasi(){
    cout<<"(";
    printf("%.2f", koor[0]);
    cout<<",";
    printf("%.2f", koor[1]);
    cout<<")"<<endl;
}

void gerak(float x, float y){
    koor[0] += x;
    koor[1] += y;
    n +=1;
    vector <int> temp;
    for (int i=0;i<2;i++){
        temp.push_back(koor[i]);
    }
    history.push_back(temp);
}

void gerak_2(float v, float t, float theta){
    float s = v*t;
    float x = s*cos((theta*3.14)/180);
    float y = s*sin((theta*3.14)/180);
    koor[0] += x;
    koor[1] += y;
    n += 1;
    vector <int> temp;
    for (int i=0;i<2;i++){
        temp.push_back(koor[i]);
    }
    history.push_back(temp);
}

void undo(){
    if (n<0){
        cout<<"Tidak Dapat di-undo"<<endl;
    }
    else {
        n -= 1;
        koor[0] = history[n][0];
        koor[1] = history[n][1];
    }
}

void redo(){
    if (n+1<history.size()){
        n += 1;
        koor[0] = history[n][0];
        koor[1] = history[n][1];    
    }
    else {
        cout<<"Tidak dapat di-redo"<<endl;
    }
}

void save(float koor[]) {
    ofstream myfile("koordinat.txt");
    if (myfile.is_open()) {
        myfile << koor[0] << " " << koor[1];
        myfile.close();
        std::cout << "Koordinat berhasil disimpan ke dalam file koordinat.txt" << std::endl;
    } else {
        std::cout << "Gagal menyimpan koordinat ke dalam file!" << std::endl;
    }
}

void load() {
    ifstream myfile("koordinat.txt");
    if (myfile.is_open()) {
        float x, y;
        myfile >> x >> y;
        koor[0] = x;
        koor[1] = y;
        myfile.close();
        cout << "Koordinat berhasil dimuat dari file koordinat.txt" << endl;
    } else {
        cout << "Gagal memuat koordinat dari file!" << endl;
    }
}

int main(){
    load();
    int w;
    vector <int> temp;
        for (int i=0;i<2;i++){
            temp.push_back(koor[i]);
        }
        history.push_back(temp);
    printf("lokasi =>");
    lokasi();
    while(true){
        cout<<"gerak(x,y)(1), gerak_2(v,t,theta)(2), undo()(3), redo()(4), lokasi()(5), save()(6)"<<endl;
        cin>>w;
        if (w==1){
            float x = 0;
            float y = 0;
            cout<<"Masukkan (x,y) : ";
            cin>>x;
            cin>>y;
            gerak(x,y);
            cout<<"lokasi =>";
            lokasi();        
        }
        else if (w==2){
            float v = 0;
            float t = 0;
            float theta = 0;
            cout<<"Masukkan (v,t,theta) : ";
            cin>>v;
            cin>>t;
            cin>>theta;
            gerak_2(v,t,theta);
            cout<<"lokasi =>";
            lokasi();
        }
        else if (w==3){
            undo();
            cout<<"lokasi =>";
            lokasi();
        }
        else if (w==4){
            redo();
            cout<<"lokasi =>";
            lokasi();
        }
        else if (w==5) {
            cout<<"lokasi =>";
            lokasi();
        }
        else if (w==6) {
            save(koor);
            break;
        }
        for (int i = 0; i<history.size();i++){
            for (int j=0; j<2;j++){
                cout<<history[i][j];
            }
            cout<<endl;
        }
    }
}