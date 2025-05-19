//$Source$
//------------------------------------------------------------------------------
//                                  JPL_Eph_DE430
//------------------------------------------------------------------------------
// Proyecto-TTI.
//
// Created: 2025/05/18
//
/** @file JPL_Eph_DE430.cpp
 * @brief Implementacion de la operacion JPL_Eph_DE430.
 *
 *  @author Rubén García Eguizábal
 *  @bug No hay bugs conocidos
 */
//------------------------------------------------------------------------------
#include "..\include\JPL_Eph_DE430.hpp"
#include "..\include\Sat_const.hpp"
#include "..\include\Cheb3D.hpp"
using namespace std;

tuple<Matrix&,Matrix&,Matrix&,Matrix&,Matrix&,Matrix&,Matrix&,Matrix&,Matrix&,Matrix&,Matrix&> JPL_Eph_DE430 (double Mjd_TDB)
{
    double JD = Mjd_TDB + 2400000.5;

    int i;
    for ( i = 1; i < PC.n_row; i++)
    {
        if(PC(i,1)<=JD & JD<=PC(i,2)){
            break;
        }
    }

    Matrix& PCtemp = extract_row(PC,i);
    
    double t1 = PCtemp(1) - 2400000.5;

    double dt = Mjd_TDB - t1;
    
    Matrix& temp =zeros(4);
    for (int j = 0; j < 4; j++){
        temp(j+1)=231+13*j;
    }

    Matrix& Cx_Earth = extract_vector(PCtemp,temp(1),temp(2)-1);
    Matrix& Cy_Earth = extract_vector(PCtemp,temp(2),temp(3)-1);
    Matrix& Cz_Earth = extract_vector(PCtemp,temp(3),temp(4)-1);
    temp = temp + 39;
    Matrix& Cx = extract_vector(PCtemp,temp(1),temp(2)-1);
    Matrix& Cy = extract_vector(PCtemp,temp(2),temp(3)-1);
    Matrix& Cz = extract_vector(PCtemp,temp(3),temp(4)-1); 
    Cx_Earth = union_vector(Cx_Earth,Cx);
    Cy_Earth = union_vector(Cy_Earth,Cy);
    Cz_Earth = union_vector(Cz_Earth,Cz);   
    int j;
    double Mjd0; 
    if (0<=dt && dt<=16){
        j=0;
        Mjd0 = t1;
    }else if(16<dt && dt<=32){
        j=1;
        Mjd0 = t1+16*j;
    }

    Matrix& r_Earth = transpose(Cheb3D(Mjd_TDB, 13.0, Mjd0, Mjd0+16, extract_vector(Cx_Earth,13*j+1,13*j+13),extract_vector(Cy_Earth,13*j+1,13*j+13),extract_vector(Cz_Earth,13*j+1,13*j+13)))*1e3;
    
    temp = zeros(4);
    for (int j = 0; j < 4; j++){
        temp(j+1)=441+13*j;
    }
    Matrix& Cx_Moon = extract_vector(PCtemp,temp(1),temp(2)-1);
    Matrix& Cy_Moon = extract_vector(PCtemp,temp(2),temp(3)-1);
    Matrix& Cz_Moon = extract_vector(PCtemp,temp(3),temp(4)-1);
    for (int i=1;i<=7;i++){
        temp = temp+39;
        Cx = extract_vector(PCtemp,temp(1),temp(2)-1);
        Cy = extract_vector(PCtemp,temp(2),temp(3)-1);
        Cz = extract_vector(PCtemp,temp(3),temp(4)-1);   
        Cx_Moon = union_vector(Cx_Moon,Cx);
        Cy_Moon = union_vector(Cy_Moon,Cy);
        Cz_Moon = union_vector(Cz_Moon,Cz);    
    }
    if (0<=dt && dt<=4){
        j=0;
        Mjd0 = t1;
    }else if(4<dt && dt<=8){
        j=1;
        Mjd0 = t1+4*j;
    }else if(8<dt && dt<=12){
        j=2;
        Mjd0 = t1+4*j;
    }else if(12<dt && dt<=16){
        j=3;
        Mjd0 = t1+4*j;
    }else if(16<dt && dt<=20){
        j=4;
        Mjd0 = t1+4*j;
    }else if(20<dt && dt<=24){
        j=5;
        Mjd0 = t1+4*j;
    }else if(24<dt && dt<=28){
        j=6;
        Mjd0 = t1+4*j;
    }else if(28<dt && dt<=32){
        j=7;
        Mjd0 = t1+4*j;
    }
    Matrix& r_Moon = transpose(Cheb3D(Mjd_TDB, 13, Mjd0, Mjd0+4, 
        extract_vector(Cx_Moon,13*j+1,13*j+13),extract_vector(Cy_Moon,13*j+1,13*j+13),extract_vector(Cz_Moon,13*j+1,13*j+13)))*1e3;
    
    temp = zeros(4);
    for (int j = 0; j < 4; j++){
        temp(j+1)=753+11*j;
    }
    Matrix& Cx_Sun = extract_vector(PCtemp,temp(1),temp(2)-1);  
    Matrix& Cy_Sun = extract_vector(PCtemp,temp(2),temp(3)-1);  
    Matrix& Cz_Sun = extract_vector(PCtemp,temp(3),temp(4)-1);  
    temp = temp + 33;
    Cx = extract_vector(PCtemp,temp(1),temp(2)-1); 
    Cy = extract_vector(PCtemp,temp(2),temp(3)-1);  
    Cz = extract_vector(PCtemp,temp(3),temp(4)-1);    
    Cx_Sun = union_vector(Cx_Sun,Cx);
    Cy_Sun = union_vector(Cy_Sun,Cy);
    Cz_Sun = union_vector(Cz_Sun,Cz);
    if (0<=dt && dt<=16){
        j=0;
        Mjd0 = t1;
    }else if(16<dt && dt<=32){
        j=1;
        Mjd0 = t1+16*j;
    }
    Matrix& r_Sun = transpose(Cheb3D(Mjd_TDB, 11, Mjd0, Mjd0+16, 
        extract_vector(Cx_Sun,11*j+1,11*j+11),extract_vector(Cy_Sun,11*j+1,11*j+11),extract_vector(Cz_Sun,11*j+1,11*j+11))) *1e3;
    
    temp = zeros(4);
    for (int j = 0; j < 4; j++){
        temp(j+1)=3+14*j;
    }
    Matrix& Cx_Mercury = extract_vector(PCtemp,temp(1),temp(2)-1);
    Matrix& Cy_Mercury = extract_vector(PCtemp,temp(2),temp(3)-1);
    Matrix& Cz_Mercury = extract_vector(PCtemp,temp(3),temp(4)-1);
    for (int i=1;i<=3;i++){
        temp = temp+42;
        Cx = extract_vector(PCtemp,temp(1),temp(2)-1);
        Cy = extract_vector(PCtemp,temp(2),temp(3)-1);
        Cz = extract_vector(PCtemp,temp(3),temp(4)-1);;
        Cx_Mercury = union_vector(Cx_Mercury,Cx);
        Cy_Mercury = union_vector(Cy_Mercury,Cy);
        Cz_Mercury = union_vector(Cz_Mercury,Cz);    
    }
    if (0<=dt && dt<=8){
        j=0;
        Mjd0 = t1;
    }else if(8<dt && dt<=16){
        j=1;
        Mjd0 = t1+8*j;
    }else if (16<dt && dt<=24){
        j=2;
        Mjd0 = t1+8*j;
    }else if(24<dt && dt<=32){
        j=3;
        Mjd0 = t1+8*j;
    }
    Matrix& r_Mercury = transpose(Cheb3D(Mjd_TDB, 14, Mjd0, Mjd0+8, 
        extract_vector(Cx_Mercury,14*j+1,14*j+14),extract_vector(Cy_Mercury,14*j+1,14*j+14),extract_vector(Cz_Mercury,14*j+1,14*j+14))) *1e3;

    temp = zeros(4);
    for (int j = 0; j < 4; j++){
        temp(j+1)=171+10*j;
    }
    Matrix& Cx_Venus = extract_vector(PCtemp,temp(1),temp(2)-1);
    Matrix& Cy_Venus = extract_vector(PCtemp,temp(2),temp(3)-1);
    Matrix& Cz_Venus = extract_vector(PCtemp,temp(3),temp(4)-1);
    temp = temp+30;
    Cx = extract_vector(PCtemp,temp(1),temp(2)-1);
    Cy = extract_vector(PCtemp,temp(2),temp(3)-1);
    Cz = extract_vector(PCtemp,temp(3),temp(4)-1);
    Cx_Venus = union_vector(Cx_Venus,Cx);
    Cy_Venus = union_vector(Cy_Venus,Cy);
    Cz_Venus = union_vector(Cz_Venus,Cz);
    if (0<=dt && dt<=16){
        j=0;
        Mjd0 = t1;
    }else if(16<dt && dt<=32){
        j=1;
        Mjd0 = t1+16*j;
    }
    Matrix& r_Venus = transpose(Cheb3D(Mjd_TDB, 10, Mjd0, Mjd0+16, 
        extract_vector(Cx_Venus,10*j+1,10*j+10),extract_vector(Cy_Venus,10*j+1,10*j+10),extract_vector(Cz_Venus,10*j+1,10*j+10))) *1e3;
    

    temp = zeros(4);

    for (int j = 0; j < 4; j++){
        temp(j+1)=309+11*j;
    }
    Matrix& Cx_Mars = extract_vector(PCtemp,temp(1),temp(2)-1);
    Matrix& Cy_Mars = extract_vector(PCtemp,temp(2),temp(3)-1);
    Matrix& Cz_Mars = extract_vector(PCtemp,temp(3),temp(4)-1);
    j=0;
    Mjd0 = t1;
    Matrix& r_Mars = transpose(Cheb3D(Mjd_TDB, 11, Mjd0, Mjd0+32, 
        extract_vector(Cx_Mars,11*j+1,11*j+11),extract_vector(Cy_Mars,11*j+1,11*j+11),extract_vector(Cz_Mars,11*j+1,11*j+11))) *1e3;
    
    temp = zeros(4);

    for (int j = 0; j < 4; j++){
        temp(j+1)=342+8*j;
    }
    Matrix& Cx_Jupiter = extract_vector(PCtemp,temp(1),temp(2)-1);
    Matrix& Cy_Jupiter = extract_vector(PCtemp,temp(2),temp(3)-1);
    Matrix& Cz_Jupiter = extract_vector(PCtemp,temp(3),temp(4)-1);
    j=0;
    Mjd0 = t1;
    Matrix& r_Jupiter = transpose(Cheb3D(Mjd_TDB, 8, Mjd0, Mjd0+32, 
        extract_vector(Cx_Jupiter,8*j+1,8*j+8),extract_vector(Cy_Jupiter,8*j+1,8*j+8),extract_vector(Cz_Jupiter,8*j+1,8*j+8))) *1e3;
    
    temp = zeros(4);

    for (int j = 0; j < 4; j++){
        temp(j+1)=366+7*j;
    }
    Matrix& Cx_Saturn = extract_vector(PCtemp,temp(1),temp(2)-1);
    Matrix& Cy_Saturn = extract_vector(PCtemp,temp(2),temp(3)-1);
    Matrix& Cz_Saturn = extract_vector(PCtemp,temp(3),temp(4)-1);
    j=0;
    Mjd0 = t1;
    Matrix& r_Saturn = transpose(Cheb3D(Mjd_TDB, 7, Mjd0, Mjd0+32, 
        extract_vector(Cx_Saturn,7*j+1,7*j+7),extract_vector(Cy_Saturn,7*j+1,7*j+7),extract_vector(Cz_Saturn,7*j+1,7*j+7)))*1e3;
    
    temp = zeros(4);

    for (int j = 0; j < 4; j++){
        temp(j+1)=387+6*j;
    }
    Matrix& Cx_Uranus = extract_vector(PCtemp,temp(1),temp(2)-1);
    Matrix& Cy_Uranus = extract_vector(PCtemp,temp(2),temp(3)-1);
    Matrix& Cz_Uranus = extract_vector(PCtemp,temp(3),temp(4)-1);
    j=0;
    Mjd0 = t1;
    Matrix& r_Uranus = transpose(Cheb3D(Mjd_TDB, 6, Mjd0, Mjd0+32, 
        extract_vector(Cx_Uranus,6*j+1,6*j+6),extract_vector(Cy_Uranus,6*j+1,6*j+6),extract_vector(Cz_Uranus,6*j+1,6*j+6)))*1e3;
    
    temp = zeros(4);

    for (int j = 0; j < 4; j++){
        temp(j+1)=405+6*j;
    }
    Matrix& Cx_Neptune = extract_vector(PCtemp,temp(1),temp(2)-1);
    Matrix& Cy_Neptune = extract_vector(PCtemp,temp(2),temp(3)-1);
    Matrix& Cz_Neptune = extract_vector(PCtemp,temp(3),temp(4)-1);
    j=0;
    Mjd0 = t1;
    Matrix& r_Neptune = transpose(Cheb3D(Mjd_TDB, 6, Mjd0, Mjd0+32, 
        extract_vector(Cx_Neptune,6*j+1,6*j+6),extract_vector(Cy_Neptune,6*j+1,6*j+6),extract_vector(Cz_Neptune,6*j+1,6*j+6)))*1e3;
    
    temp = zeros(4);

    for (int j = 0; j < 4; j++){
        temp(j+1)=423+6*j;
    }
    Matrix& Cx_Pluto = extract_vector(PCtemp,temp(1),temp(2)-1);
    Matrix& Cy_Pluto = extract_vector(PCtemp,temp(2),temp(3)-1);
    Matrix& Cz_Pluto = extract_vector(PCtemp,temp(3),temp(4)-1);
    j=0;
    Mjd0 = t1;
    Matrix& r_Pluto = transpose(Cheb3D(Mjd_TDB, 6, Mjd0, Mjd0+32, 
        extract_vector(Cx_Pluto,6*j+1,6*j+6),extract_vector(Cy_Pluto,6*j+1,6*j+6),extract_vector(Cz_Pluto,6*j+1,6*j+6)))*1e3;
    
    temp = zeros(4);

    for (int j = 0; j < 4; j++){
        temp(j+1)=819+10*j;
    }
    Matrix& Cx_Nutations = extract_vector(PCtemp,temp(1),temp(2)-1);
    Matrix& Cy_Nutations = extract_vector(PCtemp,temp(2),temp(3)-1);
    for (int i=1;i<=3;i++){
        temp = temp+20;
        Cx = extract_vector(PCtemp,temp(1),temp(2)-1);
        Cy = extract_vector(PCtemp,temp(2),temp(3)-1);
        Cx_Nutations = union_vector(Cx_Nutations,Cx);
        Cy_Nutations = union_vector(Cy_Nutations,Cy);
    }
    if (0<=dt && dt<=8){
        j=0;
        Mjd0 = t1;
    }else if(8<dt && dt<=16){
        j=1;
        Mjd0 = t1+8*j;
    }else if (16<dt && dt<=24){
        j=2;
        Mjd0 = t1+8*j;
    }else if(24<dt && dt<=32){
        j=3;
        Mjd0 = t1+8*j;
    }
    Matrix& Nutations = transpose(Cheb3D(Mjd_TDB, 10, Mjd0, Mjd0+8, 
        extract_vector(Cx_Nutations,10*j+1,10*j+10),extract_vector(Cy_Nutations,10*j+1,10*j+10),zeros(10,1)));
    
    temp = zeros(4);

    for (int j = 0; j < 4; j++){
        temp(j+1)=899+10*j;
    }
    Matrix& Cx_Librations = extract_vector(PCtemp,temp(1),temp(2)-1);
    Matrix& Cy_Librations = extract_vector(PCtemp,temp(2),temp(3)-1);
    Matrix& Cz_Librations = extract_vector(PCtemp,temp(3),temp(4)-1);
    for(int i=1;i<=3;i++){
        temp = temp+30;
        Cx = extract_vector(PCtemp,temp(1),temp(2)-1);
        Cy = extract_vector(PCtemp,temp(2),temp(3)-1);
        Cz = extract_vector(PCtemp,temp(3),temp(4)-1);
        Cx_Librations = union_vector(Cx_Librations,Cx);
        Cy_Librations = union_vector(Cy_Librations,Cy);
        Cz_Librations = union_vector(Cz_Librations,Cz);    
    }
    if (0<=dt && dt<=8){
        j=0;
        Mjd0 = t1;
    }
    else if(8<dt && dt<=16){
        j=1;
        Mjd0 = t1+8*j;
    }else if (16<dt && dt<=24){
        j=2;
        Mjd0 = t1+8*j;
    }else if(24<dt && dt<=32){
        j=3;
        Mjd0 = t1+8*j;
    }
    Matrix& Librations = transpose(Cheb3D(Mjd_TDB, 10, Mjd0, Mjd0+8, 
        extract_vector(Cx_Librations,10*j+1,10*j+10),extract_vector(Cy_Librations,10*j+1,10*j+10),extract_vector(Cz_Librations,10*j+1,10*j+10)));
    
    double EMRAT = 81.30056907419062; 
    double EMRAT1 = 1/(1+EMRAT);
    r_Earth = r_Earth-r_Moon*EMRAT1;
    r_Mercury = r_Mercury-r_Earth;
    r_Venus = r_Venus-r_Earth;
    r_Mars = r_Mars-r_Earth;
    r_Jupiter = r_Jupiter-r_Earth;
    r_Saturn = r_Saturn-r_Earth;
    r_Uranus = r_Uranus-r_Earth;
    r_Neptune = r_Neptune-r_Earth;
    r_Pluto = r_Pluto-r_Earth;
    r_Sun = r_Sun-r_Earth;
    
    return tie(r_Mercury,r_Venus,r_Earth,r_Mars,r_Jupiter,r_Saturn,r_Uranus,r_Neptune,r_Pluto,r_Moon,r_Sun);
}