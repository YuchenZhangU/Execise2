#include <iostream>
#include<math.h>
using namespace std;
class Matrix
{
public:
   Matrix();
   Matrix(size_t m,size_t n);
   Matrix(const Matrix& A);
   ~Matrix();
   void clear();
   void initializeMatrix();
   void resize(size_t newRows,size_t newColoumns);
//-------overloading functions----------------
   Matrix& operator=(const Matrix& A);
   bool operator==(const Matrix& A);
   bool operator!=(const Matrix& A);
   Matrix& operator+=(const Matrix& A);
   Matrix& operator-=(const Matrix& A);
   Matrix& operator*=(const Matrix& A);
   Matrix& operator*=(double a);
   double& operator()(size_t i,size_t j);
   const double& operator() (size_t i, size_t j) const;
   friend Matrix operator+(const Matrix& A, const Matrix& B);
   friend Matrix operator-(const Matrix& A, const Matrix& B);
   friend Matrix operator*(const Matrix& A, const Matrix& B);
   friend Matrix operator*(double a, const Matrix& A);
   friend Matrix operator*(const Matrix& A, double a );
   friend ostream& operator << (ostream& output, const Matrix& A) ;
   friend istream& operator >>(istream& input, Matrix& A);

private:
   static const size_t kAllocSize=4;
   size_t rows,columns;
   double** buf;
public:
//---------other member function---------------
   const size_t getRows() const {return rows;}   //Q==why return const??==
   size_t getColoumn() const {return columns;}
   bool IsSymmetric();
   Matrix Transpose();
   Matrix Identity();
   Matrix Identity(size_t n);
   bool LU(Matrix& L, Matrix& U);

};

//=====================Basic functions ==========================

//------------------------------Initialization function-----------
void Matrix::initializeMatrix()
{
for (size_t i=0; i<rows; i++) 
   for(size_t j=0;j<columns;j++)
      buf[i][j]=0;
}

//------------------------------Resize Function---------------------
void Matrix::resize(size_t newRows,size_t newColoumns)
{
   size_t oldRows=rows;
   size_t oldColoumns=columns;
   double** oldBuf=buf;
   rows=newRows;
   columns=newColoumns;
   buf=new double*[rows];
   for(size_t i=0;i<rows;i++)
      buf[i]=new double[columns];
   initializeMatrix();
   for (size_t i = 0; i<(oldRows<rows?oldRows:rows);i++)
      for(size_t j=0; j<(oldColoumns<columns?oldColoumns:columns);j++)
	 buf[i][j]=oldBuf[i][j];
   for(size_t i=0;i<oldRows;i++)
      delete [] oldBuf[i];
   delete [] oldBuf;
}





//====================Constructor coyp constructor & destructor==============
//---------------------------- Implemenation  -----------------------------
Matrix::Matrix() //default constructor
{
   rows=columns=kAllocSize;
   buf=new double*[rows];
   for(size_t i=0;i<rows;i++)
      buf[i]=new double[columns];
   initializeMatrix();
}

//-------------------declare an mxn matrix---------------------------------

Matrix::Matrix( size_t m,  size_t n)//declare an mxn matrix
{
   if(m!=0&&n!=0)
   {
      rows=m;
      columns=n;
      buf=new double*[rows];
      for(size_t i=0;i<rows;i++)
	 buf[i]=new double[columns];
      initializeMatrix();
   }
   else 
   { 
      cout<<"Given Matrix size should bigger than 0! ";
      cout<<"The is constructed by default size.\n";
      rows=columns=kAllocSize;
      buf=new double*[rows];
      for(size_t i=0;i<rows;i++)
	 buf[i]=new double[columns];
      initializeMatrix();
   }
      
}

Matrix::Matrix(const Matrix& A) //copy constructor
{
   if (A.rows!=0&&A.columns!=0)
   {
      rows=A.rows;
      columns=A.columns;
      buf=new double*[rows];
      for(size_t i=0;i<rows;i++)
	 buf[i]=new double[columns];
      for(size_t i=0;i<rows;i++)
	 for(size_t j=0;j<columns;j++)
	    buf[i][j]=A.buf[i][j];
   }
}


//---------------------destructor-------------------------------------------

Matrix::~Matrix()//destructor
{
   for(size_t i=0;i<rows;i++)
      delete [] buf[i];
   delete [] buf;
   buf=nullptr;
}


void Matrix::clear()
{
   if(buf!=nullptr)
   {
      for(size_t i=0;i<rows;i++)
	 delete [] buf[i];
      delete [] buf;
      buf=nullptr;
      rows=columns=0;
   }
}



//===================OVERELOADING AS GOLBAL OPERATORS==========
//Matrix A+B
Matrix operator + (const Matrix& A, const Matrix& B) 
{
   if(A.rows==B.rows&&A.columns==B.columns)    
      if(A.buf!=nullptr&&B.buf!=nullptr)      
      {
	 Matrix temp(A.rows,A.columns);
	 for(size_t i=0;i<A.rows;i++)
	    for(size_t j=0;j<A.columns;j++)
	       temp.buf[i][j]=A.buf[i][j]+B.buf[i][j];
	 return temp;
      }
      else 
      {
	 cout<<"In operation +,one of the operands is empty!\n";
	 return A;
      }
   else 
   {
      cout<<"In operation +, the two operands must have the same dimensionality!\n";
      exit(0);
   }
}

//Matrix A-B
Matrix operator - (const Matrix& A, const Matrix& B) 
{
      if(A.rows==B.rows&&A.columns==B.columns)    
      if(A.buf!=nullptr&&B.buf!=nullptr)      
      {
	 Matrix temp(A.rows,A.columns);
	 for(size_t i=0;i<A.rows;i++)
	    for(size_t j=0;j<A.columns;j++)
	       temp.buf[i][j]=A.buf[i][j]-B.buf[i][j];
	 return temp;
      }
      else 
      {
	 cout<<"In operation -,one of the operands is empty!\n";
	 return A;
      }
   else 
   {
      cout<<"In operation -, the two operands must have the same dimensionality!\n";
      exit(0);
   }
}

 //Matrix A*B
Matrix operator * (const Matrix& A, const Matrix& B)
{
   if(A.columns==B.rows)
      if(A.buf!=nullptr&&B.buf!=nullptr)  
      {
	 Matrix temp(A.rows,B.columns);
	 for(size_t i=0;i<A.rows;i++)
	    for(size_t k=0;k<A.columns;k++)
	       for(size_t j=0;j<B.columns;j++)
		  // for(size_t j=0;j<B.columns;j++)
		  //    for(size_t k=0;k<A.columns;k++)
		  temp.buf[i][j]+=(A.buf[i][k]*B.buf[k][j]);
	 return temp;
      }
      else 
      {
	 cout<<"In operation *,one of the operands is empty!\n";
	 return A;
      }
   else
   {
      cout<<"In operation *, the rows of the first operand must be the sames as the coloumns of second operand!\n";
      exit(0);
   }
}


//do a*A
Matrix operator * (double a, const Matrix& A) 
{
   if(A.buf!=nullptr)
   {
      Matrix temp(A.rows,A.columns);
      for(size_t i=0;i<A.rows;i++)
	 for(size_t j=0;j<A.columns;j++)
	    temp.buf[i][j]=a*A.buf[i][j];
	       return temp;
   }
   else 
      cout<<"In operation *, the Matrix is empty!\n";
   return A;	
}

//do A*a
Matrix operator * (const Matrix& A, double a ) 
{
   if(A.buf!=nullptr)
   {
      Matrix temp(A.rows,A.columns);
      for(size_t i=0;i<A.rows;i++)
	 for(size_t j=0;j<A.columns;j++)
	    temp.buf[i][j]=a*A.buf[i][j];
      return temp;
   }
   else 
      cout<<"In operation *, the Matrix is empty!\n";
   return A;		
}





//======================OVERLOADING AS MEM FUNCTIONS=============================

//---------------------------------Overloading = -----------------------------------
Matrix& Matrix::operator = (const Matrix& A) //overloading =
{
   clear();  
   if (A.rows!=0&&A.columns!=0)
   {
      rows=A.rows;
      columns=A.columns;
      buf=new double*[rows];
      for(size_t i=0;i<rows;i++)
	 buf[i]=new double[columns];
      for(size_t i=0;i<rows;i++)
	 for(size_t j=0;j<columns;j++)
	    buf[i][j]=A.buf[i][j];
   }
   return *this;
}

//--------------------overloading == -------------------------------------------------
bool Matrix::operator == (const Matrix& A)//overloading ==
{
   if(rows!=A.rows||columns!=A.columns)
      return false;
   else 
      for(size_t i=0;i<rows;i++)
	 for(size_t j=0;j<columns;j++)
	    if(buf[i][j]!=A.buf[i][j])
	       return false;
   return true;
}

bool Matrix::operator != (const Matrix& A)//overloading !=
{
   if(*this==A)
      return false;
   else 
      return true;
}



//---------------------------overloading += -----------------------------------------------
Matrix& Matrix::operator += (const Matrix& A) //overloading +=
{
  if(rows==A.rows&&columns==A.columns)    
      if(buf!=nullptr&&A.buf!=nullptr)      
      {
	 *this=*this+A;
	 return *this;
      }
      else 
      {
	 cout<<"In operation +=,one of the operands is empty!\n";
	 return *this;
      }
   else 
   {
      cout<<"In operation +=, the two operands must have the same dimensionality!\n";
      exit(0);
   }
}
//---------------------------Operator -= ------------------------------------------
Matrix& Matrix::operator -=(const Matrix& A) //overloading -=
{
   if(rows==A.rows&&columns==A.columns)    
      if(buf!=nullptr&&A.buf!=nullptr)      
      {
	 *this=*this-A;
	 return *this;
      }
      else 
      {
	 cout<<"In operation -=,one of the operands is empty!\n";
	 return *this;
      }
   else 
   {
      cout<<"In operation -=, the two operands must have the same dimensionality!\n";
      exit(0);
   }
}

//----------------------------overloading *= -------------------------------
Matrix& Matrix::operator *=(const Matrix& A) //overloading *=
{
  if(columns==A.rows)
      if(buf!=nullptr&&A.buf!=nullptr)  
      {
	 *this=*this*A;
	 return *this;
      }
      else 
      {
	 cout<<"In operation *=,one of the operands is empty!\n";
	 return *this;
      }
   else
   {
      cout<<"In operation *=, the rows of the first operand must be the sames as the coloumns of second operand!\n";
      exit(0);
   }
}

//------------------------------Overloading Operator *= -------------------------------------
Matrix& Matrix::operator *=(double a) //overloading *=
{   
   if(buf!=nullptr)     
      {
	 *this=*this*a;
	 return *this;
      }
      else 
      {
	 cout<<"In operation *=(number),the Matrix is empty!\n";
	 return *this;
      }
}




//------------------- access (i, j)-----------------------------------
double& Matrix::operator ()( size_t i,  size_t j)// access (i,j)
{
   if(i>=rows&&j>=columns)
      resize(i+kAllocSize,j+kAllocSize);
   else 
      if(i>=rows)
	 resize(i+kAllocSize,columns);
	 else
	    if(j>=columns)
	       resize(rows,j+kAllocSize);
   return buf[i][j];
	//return buf[i*columns+j];

}


const double& Matrix::operator() (size_t i, size_t j) const
{
   if(i>=rows||j>=columns)
   {
      cout<<"The index given is out of range!\n";
	 exit(0);
   }
   return buf[i][j];
}




//-------------------------------Overloading Operator << ----------------------------

ostream& operator << (ostream& output, const Matrix& A) 
{	
   for(size_t i=0;i<A.rows;i++)
   {
      for(size_t j=0;j<A.columns;j++)
      {
	 output << A.buf[i][j]<<"    " ;
      }
      output <<endl;
   }
   return output;
}


//-----------------------Overloading instream operator >> -----------------------------------------

istream& operator >> (istream& input, Matrix& A) 
{
   double temp;
      for(size_t i=0;i<A.rows;i++)
	 for(size_t j=0;j<A.columns;j++)
		if(input>>temp)
	    A.buf[i][j]=temp;
      return input;
}


//how terminate the input;e.g. input first two value others default


//===================Other Member Functions================
bool Matrix::IsSymmetric()
{
   if (buf!=nullptr)
   {   
      if(rows!=columns)
	 return false;
      else
      {
	 for(size_t i=0;i<rows;i++)
	    for(size_t j=i+1;j<columns;j++)
	       if(buf[i][j]!=buf[j][i])
		  return false;
	 return true;
      }
   }
   else
   {
      cout<<"Calling function IsSymmetric:the Matrix is empty!\n";
      return false;
   }
}

Matrix Matrix::Transpose()  //transpose
{
   if (buf!=nullptr)
   {   
      if(rows==columns)
      {
	 Matrix trans(rows,columns);
	 for(size_t i=0;i<rows;i++)
	 {
	    trans.buf[i][i]=buf[i][i];
	    for(size_t j=i+1;j<columns;j++)
	    {
	       trans.buf[j][i]=buf[i][j];
	       trans.buf[i][j]=buf[j][i];
	    }
	 }
	 return trans;
      }
      else
      {
	 cerr<<"Calling function Transpose:the Matrix must be square matrix!\n";
	 exit(0);
      }
   }
   else
   {
      cerr<<"Calling function Transpose:the Matrix is empty!\n";
      return *this;
   }
}


Matrix Matrix::Identity( size_t n)//make a nxn identity matrix,change "this"
{
   clear();
   rows=columns=n;
   buf=new double*[rows];
   for(size_t i=0;i<rows;i++)
      buf[i]=new double[columns];
   initializeMatrix();
   for(size_t i=0;i<rows;i++)
      buf[i][i]=1;
   return *this;	
}
Matrix Matrix::Identity()//make a identity matrix, does not change the dimentsion, change "this"
{
   if(rows==columns)
   {
      initializeMatrix();
      for(size_t i=0;i<rows;i++)
	 buf[i][i]=1;
      return *this;
   }
   else 
   {
      cerr<<"Error:Calling function Identity(). The Matrix must be square!"<<endl;
	 exit(0);
   }
}


//LU decomposition. return true if successful
bool Matrix::LU(Matrix& L, Matrix& U)
{
   if(rows>1&&columns>1)
   {
      if(rows==columns)
      {
 //initialize L and U to 0 and set diagonal elements  of A as 1;
	 L.resize(rows,columns);
	 U.resize(rows,columns);
	 L.initializeMatrix();
	 U.initializeMatrix();
	 for(size_t i=0;i<rows;i++)
	    L.buf[i][i]=1;
//Decomposition
	 for (size_t i=0;i<rows;i++)
	 {
	    for(size_t j=i;j<columns;j++)
	    {
	       double sum=0;
	       for(size_t k=0;k<i;k++)	       //debug:k<i not k<i-1
	 	  sum+=L.buf[i][k]*U.buf[k][j];
	       U.buf[i][j]=buf[i][j]-sum;	
	    }
	    if(U.buf[i][i]==0)
	       return false;
	    for(size_t j=i+1;j<columns;j++)   // j=i+1
	    {
	       double sum=0;
	       for(size_t k=0;k<i;k++)
	    	  sum+=L.buf[j][k]*U.buf[k][i];
	       L.buf[j][i]=(buf[j][i]-sum)/U.buf[i][i];
	    }
	 }
	 return true;
      }
      else
      {
	 cerr<<"Error: Calling function LU(). The LU decompostion must be operated on square Matrix!\n";
	 return false;
      }
   }
   else
   {
      cerr<<"Error: Calling function LU(). The size of the matrix should be no less than 2*2 to do LU decompostion\n";
      return false;
   } 
}
