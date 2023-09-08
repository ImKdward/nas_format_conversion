#include<fstream>
#include<iostream>
#include<string>
#include<vector>
using namespace std;
using std::vector;
//本程序用于将feko导出的.nas文件中的信息导出并存为.dat文件，以便程序使用。
int main(){
    ifstream readFile("cubeNL.nas");//输入文件
    ofstream outFile("cubeNL.dat", ios::trunc);//输出文件
    vector<string> str_vec_point;
    vector<string> str_vec_triangle;
    int material_num = 0;
    if (!readFile.is_open())
	{
		cout << "Can not open this file" << endl;
		return 0;
	}
    string temp;
    int tri_num;
    readFile>>temp;//将读到的string放到temp里面

    while(temp !="triangles:"){
        readFile>>temp;
    }
    readFile>>tri_num;
    while(temp != "GRID*"){//把前面的跳过
        readFile>>temp;
    }
    int cnt_point = 0, cnt_trangle = 0;
    int material_flag = 0; 
    while(temp != "ENDDATA")//在没遇到截止符之前
    {

        if(temp == "GRID*"){
            material_flag=0;
            cnt_point += 1;
            readFile>>temp;
            str_vec_point.push_back(temp);
            readFile>>temp;
            str_vec_point.push_back(temp);
            readFile>>temp;
            str_vec_point.push_back(temp);
            readFile>>temp;
            readFile>>temp;
            readFile>>temp;
            readFile>>temp;
            str_vec_point.push_back(temp);
        }
        else if(temp == "CTRIA3"){
            cnt_trangle += 1;
            if(material_flag==0){
                material_flag=1;
                material_num+=1;
            }
            readFile>>temp;
            str_vec_triangle.push_back(temp);
            readFile>>temp;
            readFile>>temp;
            str_vec_triangle.push_back(temp);
            readFile>>temp;
            str_vec_triangle.push_back(temp);
            readFile>>temp;
            str_vec_triangle.push_back(temp);
            str_vec_triangle.push_back(to_string(material_num));
        }
        readFile>>temp;
    }
    outFile<<cnt_point<<endl;
    for(int ii = 1; ii <= str_vec_point.size()/4; ii++)
    {
        outFile<<str_vec_point[ii * 4 - 4]<<" "<<str_vec_point[ii * 4 - 3]<<" "<<str_vec_point[ii * 4 - 2]<<" "<<str_vec_point[ii * 4 - 1]<<endl;
    }
    outFile<<cnt_trangle<<endl;
    for(int ii = 1; ii <= cnt_trangle; ii++)
    {
        outFile<<str_vec_triangle[ii * 5 - 5]<<" "<<str_vec_triangle[ii * 5 - 4]<<" "<<str_vec_triangle[ii * 5 - 3]<<" "<<str_vec_triangle[ii * 5 - 2]<<" "<<str_vec_triangle[ii * 5 - 1]<<endl;
    }
    readFile.close();
    outFile.close();
    system("pause");
    return 0;
}