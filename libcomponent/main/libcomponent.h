#ifndef LIBCOMPONENT_H
#define LIBCOMPONENT_H

/**
@param orig_resistance är ersättningsresistansen.
@param res_array är en pekare till en array med 3 resistorer som ska fyllas med värden ur E12-serien.
@return count är hur många resistorer ur E12-serien som behövdes för att ersätta orig_resistance Om inte alla 3 komponenterna behövs ska de som inte används fyllas med värdet 0. count kan anta värde mellan 0 och 3.
*/
int e_resistance(float orig_resistance, float *res_array);

#endif
