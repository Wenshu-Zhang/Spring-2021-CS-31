#include <iostream>
#include<string>
#include<cassert>
using namespace std;

int countMatches(const string a[], int n, string target){
    if (n < 0 )
        return -1;
    int count = 0;
    int i;
    for (i = 0; i < n; i++){
        if (a[i] == target)      //if a match is found, add 1 to count
            count++;
    }
    return count;
}


int detectMatch(const string a[], int n, string target){
    if (n <= 0)
        return -1;
    int i;
    for (i = 0; i < n; i++){
        if (a[i] == target)     //only return the first position that a match is found
            return i;
    }
    return -1;      //no match; thus, return -1
}


bool detectSequence(const string a[], int n, string target, int& begin, int& end){
    if (n <= 0 )        //if n is negative or has no element, return false
        return false;
    int i;
    for (i = 0; i < n; i++){
        if (a[i] == target){     //if a match is found, set begin and end to the position
            begin = i;
            end = i;
            i++;
            //detect if there is a consecutive sequence of the string
            //set end to the ending position of the sequence
            //if there is only one match, end is not changed
            while (i < n && a[i] == target){
                end = i;
                i++;
            }
            return true;//when at least one match is found, return true
        }
    }
    return false;       //if no match is found in the array, return false
}


int detectMin(const string a[], int n){
    if (n <= 0)
        return -1;
    int min = 0;        //set min to the first position in the array
    int i;
    for (i = 1; i < n; i++){        //find the min by comparing the strings in the array
        if (a[i] < a[min])
            min = i;
    }
    return min;
}


int moveToBack(string a[], int n, int pos){
    if (n < 0 || pos >= n || pos < 0)
        return -1;
    int i;
    string temp = a[pos];       //store the string at pos
    for (i = pos; i < n-1; i++){        //move the strings after pos one position to the left and eliminate the string at pos
        a[i] = a [i+1];
    }
    a[n-1] = temp;        //put the string at pos to the last position
    return pos;
}


int moveToFront(string a[], int n, int pos){
    if (n < 0 || pos < 0 || pos >= n)
        return -1;
    int i;
    string temp = a[pos];       //store the string at pos
    for (i = pos; i > 0; i--){      //move the strings before pos one position to the right and eliminate the string at pos
        a[i] = a [i-1];
    }
    a[0] = temp;        //put the string at post to the first position in the array
    return pos;
}


int detectDifference(const string a1[], int n1, const string a2[], int n2){
    if (n1 < 0 || n2 < 0 || (n1 == 0 && n2 == 0))
        return -1;
    int i;
    int limit;
    if (n1 <= n2)       //determine how many elements should be examined
        limit = n1;
    else
        limit = n2;
    for (i = 0; i < limit; i++){        //find the first difference
        if (a1[i] != a2[i])
            return i;       //return the position of the first difference
    }
    return limit;       //no difference,then return the smaller number between n1 and n2
}


int deleteDups(string a[], int n){
    if (n < 0)
        return -1;
    int r = 0;
    for (int k=0; k < n; k++){
        if (k < n && a[r] == a[r-1]){       //examine every element of the array
            string dup = a[r];
            while (k < n && a[r] == dup){     //move a repeated item to the last position
                moveToBack(a, n, r);
                k++;        //this item is examined, move to the next one
            }
            if (k!= n)      //if the loop stopped because it finished examining all items, the last item is a repeated one. Therefore, r is not incremented
                r++;        //otherwise, increment r by 1 because the item is not a repeated one
        }
        else
            r++;        //proceed to the next position that is to store a non-duplicate element
    }
    return r;
}


bool contains(const string a1[], int n1, const string a2[], int n2){
    if (n1 < 0 || n2 < 0 || n2 > n1)        //the size of a2 must be smaller than a1
        return false;
    else if (n1 >= 0 && n2 == 0)
        return true;
    int i;
    int k = 0;
    int r = 0;
    int count = 0;
    for (i = 0; i < n2; i ++){      //determine if the strings in a2 are in a1
        for (k = r; k < n1; k++){       //k starts at one position bigger than where a match was found(r): we check if the orders are the same in the two arrays
            if (a1[k] == a2[i]){
                r = k+1;
                count ++;       //count is incremented when a correct match is found
                break;      //break out of the loop to check for the next element in a2
            }
        }
    }
    if (count != n2)   //if count is not equal to n2, not all elements in a2 are found in a1
        return false;
    else     //if count is equal to n2, all elements in a2 are found in a1 in the same order
        return true;
}


int meld(const string a1[], int n1, const string a2[], int n2, string result[], int max){
    if (n1 < 0 || n2 < 0 || max < 0 || n1+n2 > max)
        return -1;
    int i;
    
    string temp = "";
    for (i = 1; i < n1; i++){       //check if a1 is in non-decreasing order
        if (a1[i-1] > a1[i])
            return -1;
    }
    for (i = 1; i < n2; i++){       //check if a2 is in non-decreasing order
        if (a2[i-1] > a2[i])
            return -1;
    }
    
    int r = 0;
    for (i = 0; i < n1; i++){       //put all items of a1 into the result array
        result[r] = a1[i];
        r++;
    }
    for (i = 0; i < n2; i++){       //put all items of a2 into the result array
        result[r] = a2[i];
        r++;
    }
    max = r;
    
    int min;
    for (int k = 0; k < max; k++){        //rearrange the array into an order from the smallest to the biggest
        min = max-1;
        for (i = max-1; i >= k; i--){    //find the min in the array after position k, where stores a determined smaller item
            if (result[i] < result[min])        //find the min among all items except the smaller items that were already put to the front positions
                min = i;
        }
        temp = result[k];      //store the element at position min
        result[k] = result[min];        //move the min element to the first position after k
        result[min] = temp;      //let the eliminated element replace the orginal element at position min, so the element will be examined again in the next round
    }
    return n1+n2;       //there is a total of n1+n2 elements in the result array
}


int split(string a[], int n, string splitter){
    if (n < 0)
        return -1;
    string temp = "";
    int max;
    int i;
    int pos;
    for (int k = n; k > 0; k--){        //rearrange the array into an order from the smallest to the biggest
        max = 0;
        for (i = 1; i < k; i++){    //find the max in the array before position k
            if (a[i] > a[max])
                max = i;
        }
        temp = a[k-1];      //store the element at position max
        a[k-1] = a[max];        //move the max element to the last position before k
        a[max] = temp;      //let the eliminated element replace the orginal element at position max; examine the element again in the next round of the loop
    }
    for (pos = 0; pos < n; pos++){      //find the first element in the rearranged array that is equal to or bigger than the splitter
        if (a[pos] >= splitter)
            return pos;
    }
    return n;       //all elements are smaller than splitter; thus, return n
}

