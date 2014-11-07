def reverseNum(num):
    return int(str(num)[::-1]);

def nextLargerPalindrome(num):
    # suppose non-negative number
    number = str(num);
    length = len(number);
    if length == 1:
        if num == 9:
            return 11;
        return num + 1;

    if length % 2:
        # Odd case
        left = int(number[0 : length / 2]);
        right = int(number[(length / 2 + 1): length]);
        mid = int(number[length / 2]);
        reverseLeft = reverseNum(left);
        if reverseLeft > right:
            #reverse left > right
            return int(str(left) + str(mid) + str(reverseLeft));
        else:
            newLeft = left * 10 + mid + 1;
            return int(str(newLeft) + str(newLeft)[0 : length / 2][::-1]);
    else:
        # Even case
        left =  int(number[0 : length / 2]);
        right = int(number[length / 2 : length]);
        reverseLeft = reverseNum(left);
        if reverseLeft > right:
            return int(str(left) + str(reverseLeft));
        else:
            newLeft = left + 1;
            if len(str(newLeft)) == length / 2:
                return int(str(newLeft) + str(newLeft)[::-1]);
            else:
                return int(str(newLeft) + str(newLeft)[0 : length / 2][::-1]);
            
        
if __name__ == "__main__":
    print nextLargerPalindrome(0);
    print nextLargerPalindrome(9);
    print nextLargerPalindrome(12);
    print nextLargerPalindrome(21);
    print nextLargerPalindrome(123)
    print nextLargerPalindrome(321);
    print nextLargerPalindrome(899);
    print nextLargerPalindrome(999);
    print nextLargerPalindrome(9899);
    print nextLargerPalindrome(9999);
