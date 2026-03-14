// https://practice.geeksforgeeks.org/problems/circular-tour-1587115620/1
int tour(petrolPump p[],int n)
    {
       int start = 0, remain = 0, loss = 0;
       for(int i=0; i<n;i++){
           remain+=p[i].petrol - p[i].distance;
           if(remain < 0){
               start = i + 1;
               loss+=remain;
               remain=0;
           }
       }
       
       return remain+loss>=0?start:-1;
    }