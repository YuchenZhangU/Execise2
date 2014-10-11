#include"VectorWithException.h"

int main()
{
  Vector a,b,c,d,e;

  string fileName="data.txt";
  try
    {
      Read(fileName,b);       // data is 1 2 3 4 5 6 7 8 9
      Assign(a,b);            //test Assign
      cout<<Equal(a,b)<<endl<<Equal(a,c)<<endl;  //test Equal should be 1 0
      Add(a,b,c);            //test Add c should be 2 4 6....
      Write("output.txt",c);
      Subtract(c,a,d);       //d should be 1 2 3....
      Write("output.txt",d);
      Multiply(10,a,d);      //d should be 10 20 30...
      Write("output.txt",d);
      double n=Multiply(a,d);//n should equate to 1*10+2*20.....=2850
      cout<<n<<endl;
      Multiply(a,e);         //test exception throw in Multiply function
      Clear(a);
      Clear(b);
      Clear(c);
      Clear(d);
    }

  catch (const invalid_argument& e)
    {
      cerr<<"Unable to open file: "<<fileName<<endl;
      return 1;
    }
  catch (const runtime_error& e)
    {
      cerr<<"Error reading file: "<<fileName<<endl;
      return 1;
    }
  catch(const int& e)
    {
      cerr<<"Unable to  Multiply with the two given Vectors!\n";
      return 1;
    }
  return 0;
}
