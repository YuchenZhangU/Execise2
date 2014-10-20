#include "Matrix.h"
//-----------------------------test--------------------
int main()
{
   Matrix a(0,0),b(2,2),c(4,4),d,L,U;
//    cout<<a.getRows()<<endl<<a.getColoumn()<<endl;
//    // a(24,24)=21;
//    // cout<<a.getRows()<<endl;
//    cin>>b;
//    cout<<"b:"<<endl<<b<<endl;
//    a=b.Transpose();
//    cout<<"a:"<<endl<<a<<endl<<a*b;
// //---------------------test IsSymmetric-------------
//    cout<<a.IsSymmetric()<<endl;
// //---------------------test Identity----------
//    cout<<a.Identity()<<endl;
//    cout<<a.Identity(5)<<endl;
// //---------------------test LU-----------------
//    b.LU(L,U);
//    cout<<L<<endl<<U;
   for(size_t i=0;i<4;i++)
      for(size_t j=0;j<4;j++)
	 c(i,j)=(i+1)*4+j+1;
   cout<<c<<endl;
   cout<<c.LU(L,U)<<endl;
   cout<<L<<endl<<U;
//-----------------test + - * += -= *=---------------
   // a=a+b;
   // cout<<"a:"<<endl<<a<<endl;
   // c=a*b;
   // cout<<"c:"<<endl<<c<<endl;
   // d=b*2;
   // cout<<"d:"<<endl<<d<<endl;
   // a+=b;
   // cout<<"a:"<<endl<<a<<endl;
   // d*=b;
   // cout<<"d:\n"<<d;
   // if(a==b)
   //    cout<<"haha\n";
   // if(a!=c)
   //    cout<<"ahaha\n";
   // for (size_t i = 0; i <a.getRows(); i++)
   //    for(size_t j=0;j<a.getRows();j++)
   // 	 a(i,j)=i*j;
   // cout<<a;
   // cout << a(1,1) << endl;
   return 0;
}
      
