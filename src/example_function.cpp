int corn = 10;
bool heat = true; 
int poppedCorn = 0;

int pop();                  //Bogus function 

/*********************************************************************************************
 * @brief                   Function that enables simulation of popcorn making
 * @param corn              Input of corn that has to be popped (Integer)
 * @param heat              Heating boolean (true/false) 
 * @return                  Returns int 'poppedCorn' (Finished product)
 *********************************************************************************************/
int popcornMaker(int corn, bool heat) {

if (heat == true)
{
    for (int i = 0; i < corn; i++)
    {
        pop();              // Bogus function
        poppedCorn++;       // 1 corn -> 1 popcorn
    }

return poppedCorn;          // Return all of the popcorns
}
}
