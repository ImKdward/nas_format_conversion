#include<fstream>
#include<iostream>
#include<string>
#include<vector>
using namespace std;
using std::vector;

//本程序用于将feko导出的.nas文件中的信息导出并存为.dat文件，以便程序使用。
int main(){
    string filename = "test";
    ifstream readFile(filename + ".nas");//打开文件
    ofstream outFile(filename + ".dat", ios::trunc);//关闭文件
    vector<string> str_vec;
    if (!readFile.is_open())
	{
		cout << "Can not open this file" << endl;
		return 0;
	}
    string temp;
    readFile>>temp;//将读到的string放到temp里面

    while(temp != "GRID*"){//把前面的跳过
        readFile>>temp;
    }
    int cnt_point = 0, cnt_trangle = 0;
    while(temp != "ENDDATA")//在没遇到截止符之前
    {
        if(temp == "GRID*"){
            cnt_point += 1;
            readFile>>temp;
            readFile>>temp;
            str_vec.push_back(temp);
            readFile>>temp;
            str_vec.push_back(temp);
            readFile>>temp;
            readFile>>temp;
            readFile>>temp;
            readFile>>temp;
            str_vec.push_back(temp);
        }
        else if(temp == "CTRIA3"){
            cnt_trangle += 1;
            readFile>>temp;
            readFile>>temp;
            readFile>>temp;
            str_vec.push_back(temp);
            readFile>>temp;
            str_vec.push_back(temp);
            readFile>>temp;
            str_vec.push_back(temp);
        }
        readFile>>temp;
    }
    outFile<<cnt_point<<endl;
    for(int ii = 1; ii <= cnt_point; ii++)
    {
        outFile<<ii<<" "<<str_vec[ii * 3 - 3]<<" "<<str_vec[ii * 3 - 2]<<" "<<str_vec[ii * 3 - 1]<<endl;
    }
    outFile<<cnt_trangle<<endl;
    for(int ii = 1; ii <= cnt_trangle; ii++)
    {
        outFile<<ii<<" "<<str_vec[cnt_point * 3 + ii * 3 - 3]<<" "<<str_vec[cnt_point * 3 + ii * 3 - 2]<<" "<<str_vec[cnt_point * 3 + ii * 3 - 1]<<endl;
    }
    readFile.close();
    outFile.close();
    //system("pause");
    return 0;
}