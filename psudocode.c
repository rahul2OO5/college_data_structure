

pattern(int *const array, int *const arr, int size, int left, int right,
        int buffer) SET mid equal to(left + right) /
    2;
if (left is equal to mid or right is equal to mid)
  then return;
END IF SET position equal to buffer + 2;

if (position is less than size)
  then array[mid] equal to arr[position] else return;
END IF

    pattern(array, arr, size, left, mid, 2 * buffer + 1);
pattern(array, arr, size, mid, right, 2 * buffer + 2);

// we use 2*buffer + 1 for going to the left side of the tree as left side index
// values are odd we use 2*buffer + 2 for going to the right side of the tree as
// right side index values are even
