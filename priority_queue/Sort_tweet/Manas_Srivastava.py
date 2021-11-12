"""
Author: Manas Srivastava mastermanas805@gmail.com

Approach:
I have used priority queue approach to solve this question. Priority queue is used via heapq package. 
It's an inbuilt python package. 
"""

import heapq #for using heap in python
class Node(object):

    """
    Class used to store the input values and compare the given class objects.
    Used to support custom type of comparison with heapq.heapify() function.
    """
    def __init__(self, name: str ,val: int):
        self.name = name
        self.val = val

    def __repr__(self): # Used for print value of the object
        return f'{self.name} {self.val}'

    def __lt__(self, other):
        if self.val == other.val:
            return self.name < other.name
        
        return self.val > other.val
        
def main():
    t = int(input()) # Input no of test cases
    while(t):
        x = n = int(input()) # Input no of input values
        d = {}
        while(x):
            name, tweet = input().split(" ") #input name and tweet
            if d.get(name):
                d[name] += 1
            else:
                d[name] = 1
            x-=1
        
        l = [Node(i, d[i]) for i in d]
        heapq.heapify(l) #creating max heap out of the given list
        
        x = l[0].val
        f = True
        while(l and f):
            obj = heapq.heappop(l) # getting top of the priority queue
            if obj.val == x:
                print(obj)
            else:
                break
        
        t-=1

if __name__=="__main__":
    main()
