Create a hash table with a simple hashing function:

All values are names of length <= 10 characters
All keys are the last letter of the names

On collisions, try to add to the next position in the array until an empty element is found
Elements in the array can have three states:
    - Never Used: Empty element, has never been filled
    - Occupied: Element is currently used
    - Tombstone: Previously filled element that has been deleted

