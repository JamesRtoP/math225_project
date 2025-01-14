#include "source.hpp"
#include "commandLine.hpp"


double outsideTheRootPos(double a, double b, double c, double insideRoot)
{
	return (-1 * b + sqrt(insideRoot))/(2*a);

}

double outsideTheRootNeg(double a, double b, double c, double insideRoot)
{
	return (-1 * b + sqrt(insideRoot))/(2*a);

}

double insideTheRoot(double a, double b, double c)
{
	return b*b-4*a*c;
}

double quadraticFormulaUnsafePositiveRoot(double a, double b, double c)//no check for negative sqrt
{
	double root = sqrt(b*b-4*a*c);
	return (0-b+root)/2*a;
}

double quadraticFormulaUnsafeNegativeRoot(double a, double b, double c)//no check for negative sqrt
{
	double root = sqrt(b*b-4*a*c);
	return (0-b-root)/2*a;
}




bool isDouble(const std::string& checkMe)
{
	bool is_double = true;
	bool seenDecimal = false;
	if(checkMe.length() == 0)
	{
		is_double = false;
	}
	else
	{
		for(int i = 0; checkMe[i] != '\0'; i++)
		{
			if(!(isdigit(checkMe[i])||(i == 0 && checkMe[i] == '-')))
			{
				if(checkMe[i] =='.')
				{
					if(seenDecimal)
					{
						is_double = false;
					}
					else
					{
						seenDecimal = true;
					}
				}
				else
				{
					is_double = false;
				}
			}
			
		}
	}
	return is_double;
	
}
/*standard library function stod
double makeDouble(const std::string& makeMeDouble)
{
	double returnMe = 0;
	bool negative = false;
	bool seenDecimal = false;
	int i = 0;
	if(makeMeDouble[0] == '-')
	{
		i = 1;
		negative = -1;
	}
	else
	{

	}
	for(; makeMeDouble[i] != '\0'; i++)
	{
		returnMe = 
	}
}
*/