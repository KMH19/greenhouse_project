// This function showcases a way of commenting code with the use of brief, param and return commands

int corn = 10;
bool heat = true; 
int poppedCorn = 0;

void pop(){
    poppedCorn++;   // 1 corn -> 1 popcorn
}; // Function 'pop' end

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
        pop();                    
    } 

return poppedCorn;          // Return all of the popcorns
} // If statement end
} // Function 'popcornMaker' end