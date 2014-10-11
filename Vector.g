#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<stdexcept>
using namespace std;
struct Vector
{
//Modified: give initial value while Vector is constructed
  size_t num=0;
  double* buf=NULL;
};

void Clear(Vector& A)
{
  if (A.buf!=NULL)
    {
      delete [] A.buf;
      A.num=0;
    }
}



bool Read(const string& filename,Vector& A)
{
  size_t counter=0;
  size_t i=0;
  ifstream fin(filename);
  if(fin.fail())
    {
      //fail to open the file throw an exception
      throw invalid_argument("");
      return false;
    }
  //count the length of the input file 
  while(fin>>i)
    {
      counter++;
    }
  //judge whether we succeed to  read the file 
  if(fin.eof())
      fin.close();
  else
    {
      fin.close();
      throw runtime_error("");
      return false;
    }
  A.num=counter;
  //return the ifstream to the beginning of the file
  fin.open(filename);
  //read numbers
  A.buf=new double[A.num];
  i=0;
  while( fin>>A.buf[i])
    {
      i++;
    }
  fin.close();
  return true;
}

bool Write(const string& filename,const Vector& A)
{
  ofstream fout(filename,ofstream::app);
  if(fout.fail())
    return false;
  for(size_t i=0;i<A.num;i++)
    fout<<A.buf[i]<<" ";
  fout<<endl;
  return true;
}


//add functions Assign, Initialize & Clear in this cpp file
void  Assign (Vector& A,const Vector& B)
{
  if (A.num!=0)
    Clear(A);
  A.num=B.num;
  A.buf=new double [B.num];
  for(size_t i=0;i<A.num;i++)
    A.buf[i]=B.buf[i];
}



bool Equal(const Vector& A,const  Vector& B)
{
  if(A.num!=B.num)
    return false;
  else
    if(A.num==0)
      {
	cout<<"The two vectors are both empty\n";
	return true;
      }
    else
      {
	for(size_t i=0;i<A.num;i++)
	  {
	    if(A.buf[i]!=B.buf[i])
	      return false;
	  }
      }
  return true;
}

// C=A+B,if A or B is empty return false
bool Add(const Vector&  A,const Vector& B, Vector& C)
{
  if(A.num!=B.num)
    return false;
  if(A.num==0)
    return false;
  if(C.num!=0)
    Clear(C);
  C.num=A.num;
  C.buf=new double[C.num];
  for(size_t i=0;i<A.num;i++)
    C.buf[i]=A.buf[i]+B.buf[i];
  return true;
}



//C=A-B; If A or B is empty return false
bool Subtract(const Vector& A,const Vector& B, Vector& C)
{
  if(A.num!=B.num)
    return false;
  if(A.num==0)
    return false;
  if(C.num!=0)
    Clear(C);
  C.num=A.num;
  C.buf=new double[C.num];
  for(size_t i=0;i<A.num;i++)
    C.buf[i]=A.buf[i]-B.buf[i];
  return true;
}

//C=a*B;
bool Multiply(double a, const Vector& B, Vector& C)
{
  if(B.num==0)
    return false;
  if(C.num!=0)
    Clear(C);
  C.num=B.num;
  C.buf=new double[C.num];
  for(size_t i=0;i<B.num;i++)
    C.buf[i]=a*B.buf[i];
  return true;
}

//dot product; throw & catch should be used??
double Multiply(const Vector& A, const Vector& B)
{
  double result=0;
  if(A.num!=B.num)
    throw 1;
  if(A.num==0)
    throw 2;
  for(size_t i=0;i<A.num;i++)
    result+=A.buf[i]*B.buf[i];
  return result;
}
