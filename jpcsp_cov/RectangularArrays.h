#pragma once

//----------------------------------------------------------------------------------------
//	Copyright © 2007 - 2022 Tangible Software Solutions, Inc.
//	This class can be used by anyone provided that the copyright notice remains intact.
//
//	This class includes methods to convert Java rectangular arrays (jagged arrays
//	with inner arrays of the same length).
//----------------------------------------------------------------------------------------
class RectangularArrays
{
public:
    static float*** RectangularFloatArray(int size1, int size2, int size3)
    {
        float*** newArray = new float**[size1];
        for (int array1 = 0; array1 < size1; array1++)
        {
            newArray[array1] = new float*[size2];
            if (size3 > -1)
            {
                for (int array2 = 0; array2 < size2; array2++)
                {
                    newArray[array1][array2] = new float[size3] {};
                }
            }
        }

        return newArray;
    }

    static long long*** RectangularLongLongArray(int size1, int size2, int size3)
    {
        long long*** newArray = new long long**[size1];
        for (int array1 = 0; array1 < size1; array1++)
        {
            newArray[array1] = new long long*[size2];
            if (size3 > -1)
            {
                for (int array2 = 0; array2 < size2; array2++)
                {
                    newArray[array1][array2] = new long long[size3] {};
                }
            }
        }

        return newArray;
    }

    static std::any** RectangularStdAnyArray(int size1, int size2)
    {
        std::any** newArray = new std::any*[size1];
        for (int array1 = 0; array1 < size1; array1++)
        {
            newArray[array1] = new std::any[size2] {};
        }

        return newArray;
    }
};
