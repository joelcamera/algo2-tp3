// g++ -g tests.cpp -o tests
// valgrind --leak-check=full -v ./tests

#include "diccNat.h"
#include "test.h"
#include <iostream>
#include <fstream>

using namespace std;


void test_constructor_vacio(){
	diccNat<int> a1;
	ASSERT(a1.EsVacio());
	diccNat<char> a2;
	ASSERT(a2.EsVacio());
	diccNat<int*> a3;
	ASSERT(a3.EsVacio());
	diccNat< diccNat<long>* > a4;
	ASSERT(a4.EsVacio());
}

void test_definir_definido_significado(){
	diccNat<bool> a1;
	bool par=true, impar=false;

	ASSERT(a1.EsVacio());
	ASSERT_EQ(a1.CantClaves(), 0);
	ASSERT(!a1.Definido(5));
	a1.Definir(5, impar);
	ASSERT(!a1.EsVacio());
	ASSERT_EQ(a1.CantClaves(), 1);
	ASSERT(a1.Definido(5));
	ASSERT_EQ(a1.Significado(5), false);
	ASSERT(!a1.Definido(4));
	a1.Definir(4, par);
	ASSERT(!a1.EsVacio());
	ASSERT_EQ(a1.CantClaves(), 2);
	ASSERT(a1.Definido(4));
	ASSERT_EQ(a1.Significado(4), true);
	ASSERT(!a1.Definido(1));
	a1.Definir(1, impar);
	ASSERT(!a1.EsVacio());
	ASSERT_EQ(a1.CantClaves(), 3);
	ASSERT(a1.Definido(1));
	ASSERT_EQ(a1.Significado(1), false);
	ASSERT(!a1.Definido(3));
	a1.Definir(3, impar);
	ASSERT(!a1.EsVacio());
	ASSERT_EQ(a1.CantClaves(), 4);
	ASSERT(a1.Definido(3));
	ASSERT_EQ(a1.Significado(3), false);
	ASSERT(!a1.Definido(8));
	a1.Definir(8, par);
	ASSERT(!a1.EsVacio());
	ASSERT_EQ(a1.CantClaves(), 5);
	ASSERT(a1.Definido(8));
	ASSERT_EQ(a1.Significado(8), true);
	ASSERT(!a1.Definido(7));
	a1.Definir(7, impar);
	ASSERT(!a1.EsVacio());
	ASSERT_EQ(a1.CantClaves(), 6);
	ASSERT(a1.Definido(7));
	ASSERT_EQ(a1.Significado(7), false);
	ASSERT(!a1.Definido(12));
	a1.Definir(12, par);
	ASSERT(!a1.EsVacio());
	ASSERT_EQ(a1.CantClaves(), 7);
	ASSERT(a1.Definido(12));
	ASSERT_EQ(a1.Significado(12), true);
	ASSERT(!a1.Definido(10));
	a1.Definir(10, par);
	ASSERT(!a1.EsVacio());
	ASSERT_EQ(a1.CantClaves(), 8);
	ASSERT(a1.Definido(10));
	ASSERT_EQ(a1.Significado(10), true);
	ASSERT(!a1.Definido(13));
	a1.Definir(13, impar);
	ASSERT(!a1.EsVacio());
	ASSERT_EQ(a1.CantClaves(), 9);
	ASSERT(a1.Definido(13));
	ASSERT_EQ(a1.Significado(13), false);

	char c;
	diccNat<char> a2;
	ASSERT(a2.EsVacio());
	ASSERT_EQ(a2.CantClaves(), 0);
	ASSERT(!a2.Definido(5));
	c = 'a';
	a2.Definir(5, c);
	ASSERT(!a2.EsVacio());
	ASSERT_EQ(a2.CantClaves(), 1);
	ASSERT(a2.Definido(5));
	ASSERT_EQ(a2.Significado(5), 'a');
	ASSERT(!a2.Definido(1));
	c = 'b';
	a2.Definir(1, c);
	ASSERT(!a2.EsVacio());
	ASSERT_EQ(a2.CantClaves(), 2);
	ASSERT(a2.Definido(1));
	ASSERT_EQ(a2.Significado(1), 'b');
	ASSERT(!a2.Definido(3));
	c = 'c';
	a2.Definir(3, c);
	ASSERT(!a2.EsVacio());
	ASSERT_EQ(a2.CantClaves(), 3);
	ASSERT(a2.Definido(3));
	ASSERT_EQ(a2.Significado(3), 'c');
	ASSERT(!a2.Definido(4));
	c = 'd';
	a2.Definir(4, c);
	ASSERT(!a2.EsVacio());
	ASSERT_EQ(a2.CantClaves(), 4);
	ASSERT(a2.Definido(4));
	ASSERT_EQ(a2.Significado(4), 'd');
	ASSERT(!a2.Definido(2));
	c = 'e';
	a2.Definir(2, c);
	ASSERT(!a2.EsVacio());
	ASSERT_EQ(a2.CantClaves(), 5);
	ASSERT(a2.Definido(2));
	ASSERT_EQ(a2.Significado(2), 'e');
	ASSERT(!a2.Definido(8));
	c = 'f';
	a2.Definir(8, c);
	ASSERT(!a2.EsVacio());
	ASSERT_EQ(a2.CantClaves(), 6);
	ASSERT(a2.Definido(8));
	ASSERT_EQ(a2.Significado(8), 'f');
	ASSERT(!a2.Definido(7));
	c = 'g';
	a2.Definir(7, c);
	ASSERT(!a2.EsVacio());
	ASSERT_EQ(a2.CantClaves(), 7);
	ASSERT(a2.Definido(7));
	ASSERT_EQ(a2.Significado(7), 'g');
	ASSERT(!a2.Definido(9));
	c = 'h';
	a2.Definir(9, c);
	ASSERT(!a2.EsVacio());
	ASSERT_EQ(a2.CantClaves(), 8);
	ASSERT(a2.Definido(9));
	ASSERT_EQ(a2.Significado(9), 'h');
	ASSERT(!a2.Definido(15));
	c = 'i';
	a2.Definir(15, c);
	ASSERT(!a2.EsVacio());
	ASSERT_EQ(a2.CantClaves(), 9);
	ASSERT(a2.Definido(15));
	ASSERT_EQ(a2.Significado(15), 'i');
	ASSERT(!a2.Definido(11));
	c = 'j';
	a2.Definir(11, c);
	ASSERT(!a2.EsVacio());
	ASSERT_EQ(a2.CantClaves(), 10);
	ASSERT(a2.Definido(11));
	ASSERT_EQ(a2.Significado(11), 'j');
}

void test_borrar(){
	bool signfalse = false, signtrue = true;

	diccNat<bool> a;
	ASSERT(a.EsVacio());
	ASSERT_EQ(a.CantClaves(), 0);

//	Caso: 		  5					X
//              	     ->
//             		     ->
//

	a.Definir(5,signfalse);
	ASSERT(!a.EsVacio());
	ASSERT_EQ(a.CantClaves(), 1);
	a.Borrar(5);
	ASSERT(a.EsVacio());
	ASSERT(!a.Definido(5));
	ASSERT_EQ(a.CantClaves(), 0);


//	Caso:    5            3               X
//          /      ->            ->
//         3       ->            ->
//

	a.Definir(5,signfalse);
	ASSERT(a.Definido(5));
	ASSERT_EQ(a.CantClaves(), 1);
	a.Definir(3,signfalse);
	ASSERT(a.Definido(3));
	ASSERT_EQ(a.CantClaves(), 2);
	a.Borrar(5);
	ASSERT(!a.Definido(5));
	ASSERT_EQ(a.CantClaves(), 1);
	ASSERT(a.Definido(3));
	a.Borrar(3);
	ASSERT(!a.Definido(3));
	ASSERT_EQ(a.CantClaves(), 0);
	ASSERT(a.EsVacio());


//	Caso:     5            5               X
//           /      ->            ->
//          3       ->            ->
//

	a.Definir(5,signfalse);
	a.Definir(3,signfalse);
	ASSERT(!a.EsVacio());
	ASSERT(a.Definido(5));
	ASSERT(a.Definido(3));
	ASSERT_EQ(a.CantClaves(), 2);
	a.Borrar(3);
	ASSERT(!a.Definido(3));
	ASSERT(a.Definido(5));
	ASSERT_EQ(a.CantClaves(), 1);
	a.Borrar(5);
	ASSERT(!a.Definido(5));
	ASSERT_EQ(a.CantClaves(), 0);
	ASSERT(a.EsVacio());


//	Caso:   5              5               X
//           \     ->             ->
//            6    ->             ->
//

	a.Definir(5,signfalse);
	a.Definir(6,signfalse);
	ASSERT(!a.EsVacio());
	ASSERT(a.Definido(5));
	ASSERT(a.Definido(6));
	ASSERT_EQ(a.CantClaves(), 2);
	a.Borrar(6);
	ASSERT(!a.Definido(6));
	ASSERT(a.Definido(5));
	ASSERT_EQ(a.CantClaves(), 1);
	a.Borrar(5);
	ASSERT(!a.Definido(5));
	ASSERT_EQ(a.CantClaves(), 0);
	ASSERT(a.EsVacio());


//	Caso:   5            6               X
//           \    ->            ->
//            6   ->            ->
//

	a.Definir(5,signfalse);
	a.Definir(6,signfalse);
	ASSERT(!a.EsVacio());
	ASSERT(a.Definido(5));
	ASSERT(a.Definido(6));
	ASSERT_EQ(a.CantClaves(), 2);
	a.Borrar(5);
	ASSERT(!a.Definido(5));
	ASSERT(a.Definido(6));
	ASSERT_EQ(a.CantClaves(), 1);
	a.Borrar(6);
	ASSERT(!a.Definido(6));
	ASSERT_EQ(a.CantClaves(), 0);
	ASSERT(a.EsVacio());


//	Caso:    5            6               6               X
//          / \    ->    /        ->             ->
//         3   6   ->   3         ->             ->
//

	a.Definir(5,signfalse);
	a.Definir(6,signtrue);
	a.Definir(3,signfalse);
	ASSERT(!a.EsVacio());
	ASSERT(a.Definido(5));
	ASSERT(a.Definido(3));
	ASSERT(a.Definido(6));
	ASSERT_EQ(a.CantClaves(), 3);
	a.Borrar(5);
	ASSERT(!a.Definido(5));
	ASSERT(a.Definido(6));
	ASSERT(a.Definido(3));
	ASSERT_EQ(a.CantClaves(), 2);
	a.Borrar(3);
	ASSERT(!a.Definido(3));
	ASSERT(a.Definido(6));
	ASSERT_EQ(a.CantClaves(), 1);
	a.Borrar(6);
	ASSERT(!a.Definido(6));
	ASSERT_EQ(a.CantClaves(), 0);
	ASSERT(a.EsVacio());


//	Caso:    5            5               6               X
//          / \    ->      \      ->             ->
//         3   6   ->       6     ->             ->
//

	a.Definir(5,signfalse);
	a.Definir(6,signtrue);
	a.Definir(3,signfalse);
	ASSERT(!a.EsVacio());
	ASSERT(a.Definido(5));
	ASSERT(a.Definido(3));
	ASSERT(a.Definido(6));
	ASSERT_EQ(a.CantClaves(), 3);
	a.Borrar(3);
	ASSERT(!a.Definido(3));
	ASSERT(a.Definido(5));
	ASSERT(a.Definido(6));
	ASSERT_EQ(a.CantClaves(), 2);
	a.Borrar(5);
	ASSERT(!a.Definido(5));
	ASSERT(a.Definido(6));
	ASSERT_EQ(a.CantClaves(), 1);
	a.Borrar(6);
	ASSERT(!a.Definido(6));
	ASSERT_EQ(a.CantClaves(), 0);
	ASSERT(a.EsVacio());


//  Caso:       5            5               3               X
//	           / \    ->    /        ->             ->
//	          3   6   ->   3         ->             ->
//	 

	a.Definir(5,signfalse);
	a.Definir(6,signtrue);
	a.Definir(3,signfalse);
	ASSERT(!a.EsVacio());
	ASSERT(a.Definido(5));
	ASSERT(a.Definido(3));
	ASSERT(a.Definido(6));
	ASSERT_EQ(a.CantClaves(), 3);
	a.Borrar(6);
	ASSERT(!a.Definido(6));
	ASSERT(a.Definido(5));
	ASSERT(a.Definido(3));
	ASSERT_EQ(a.CantClaves(), 2);
	a.Borrar(5);
	ASSERT(!a.Definido(5));
	ASSERT(a.Definido(3));
	ASSERT_EQ(a.CantClaves(), 1);
	a.Borrar(3);
	ASSERT(!a.Definido(6));
	ASSERT_EQ(a.CantClaves(), 0);
	ASSERT(a.EsVacio());


//  Caso:       5              3                            
//	           /      ->      / \       -> BORRO ARBOL
//	          3       ->     1   4      -> CON CASO ANTERIOR 
//	         / \      ->                ->
//	        1   4     ->                -> 
//	 

	a.Definir(5,signfalse);
	a.Definir(3,signfalse);
	a.Definir(1,signfalse);
	a.Definir(4,signtrue);
	ASSERT(!a.EsVacio());
	ASSERT(a.Definido(5));
	ASSERT(a.Definido(3));
	ASSERT(a.Definido(1));
	ASSERT(a.Definido(4));
	ASSERT_EQ(a.CantClaves(), 4);
	a.Borrar(5);
	ASSERT(!a.Definido(5));
	ASSERT(a.Definido(1));
	ASSERT(a.Definido(4));
	ASSERT(a.Definido(3));
	ASSERT_EQ(a.CantClaves(), 3);
	a.Borrar(3);
	a.Borrar(1);
	a.Borrar(4);
	ASSERT(!a.Definido(1));
	ASSERT(!a.Definido(4));
	ASSERT(!a.Definido(3));
	ASSERT_EQ(a.CantClaves(), 0);
	ASSERT(a.EsVacio());


//   Caso:      5                 10                         
//	             \        ->      / \      -> BORRO ARBOL
//	              10      ->     6   13    -> CON CASO ANTERIOR 
//	              / \     ->               ->
//	             6   13   ->               -> 
//	 

	a.Definir(5,signfalse);
	a.Definir(10,signtrue);
	a.Definir(13,signfalse);
	a.Definir(6,signtrue);
	ASSERT(!a.EsVacio());
	ASSERT(a.Definido(5));
	ASSERT(a.Definido(13));
	ASSERT(a.Definido(10));
	ASSERT(a.Definido(6));
	ASSERT_EQ(a.CantClaves(), 4);
	a.Borrar(5);
	ASSERT(!a.Definido(5));
	ASSERT(a.Definido(13));
	ASSERT(a.Definido(10));
	ASSERT(a.Definido(6));
	ASSERT_EQ(a.CantClaves(), 3);
	a.Borrar(13);
	a.Borrar(10);
	a.Borrar(6);
	ASSERT(!a.Definido(13));
	ASSERT(!a.Definido(10));
	ASSERT(!a.Definido(6));
	ASSERT_EQ(a.CantClaves(), 0);
	ASSERT(a.EsVacio());


//  Caso:       9                     11                       
//	          /   \         ->       /   \        -> BORRO ARBOL
//	         5     15       ->      5     15      -> CON CASO ANTERIOR 
//	        / \    /  \     ->     / \    / \     ->
//	       3   7  12  19    ->    3   7  12  19   -> 
//	          /  /  \       ->       /     \      ->
//	         6  11  14      ->      6       14    ->
//	 

	a.Definir(9,signfalse);
	a.Definir(5,signfalse);
	a.Definir(15,signfalse);
	a.Definir(7,signfalse);
	a.Definir(6,signtrue);
	a.Definir(3,signfalse);
	a.Definir(12,signtrue);
	a.Definir(11,signtrue);
	a.Definir(14,signtrue);
	a.Definir(19,signfalse);
	ASSERT(!a.EsVacio());
	ASSERT(a.Definido(9));
	ASSERT(a.Definido(5));
	ASSERT(a.Definido(6));
	ASSERT(a.Definido(3));
	ASSERT(a.Definido(7));
	ASSERT(a.Definido(11));
	ASSERT(a.Definido(12));
	ASSERT(a.Definido(14));
	ASSERT(a.Definido(15));
	ASSERT(a.Definido(19));
	ASSERT_EQ(a.CantClaves(), 10);
	a.Borrar(9);
	ASSERT(!a.Definido(9));
	ASSERT(a.Definido(5));
	ASSERT(a.Definido(6));
	ASSERT(a.Definido(3));
	ASSERT(a.Definido(7));
	ASSERT(a.Definido(11));
	ASSERT(a.Definido(12));
	ASSERT(a.Definido(14));
	ASSERT(a.Definido(15));
	ASSERT(a.Definido(19));
	ASSERT_EQ(a.CantClaves(), 9);
	a.Borrar(5);
	a.Borrar(6);
	a.Borrar(3);
	a.Borrar(7);
	a.Borrar(11);
	a.Borrar(12);
	a.Borrar(15);
	a.Borrar(14);
	a.Borrar(19);
	ASSERT(!a.Definido(5));
	ASSERT(!a.Definido(6));
	ASSERT(!a.Definido(3));
	ASSERT(!a.Definido(7));
	ASSERT(!a.Definido(11));
	ASSERT(!a.Definido(12));
	ASSERT(!a.Definido(14));
	ASSERT(!a.Definido(15));
	ASSERT(!a.Definido(19));
	ASSERT_EQ(a.CantClaves(), 0);
	ASSERT(a.EsVacio());


//   Caso:       11                  12     
//	            /   \        ->     /   \        -> BORRO ARBOL
//	           5     15      ->    5     15      -> CON CASO ANTERIOR 
//	          / \    / \     ->   / \    / \     ->
//	         3   7  12  19   ->  3   7  14  19   -> 
//	            /     \      ->     /            ->
//	           6       14    ->    6             ->
//	 

	a.Definir(11,signfalse);
	a.Definir(5,signfalse);
	a.Definir(15,signfalse);
	a.Definir(7,signfalse);
	a.Definir(6,signtrue);
	a.Definir(3,signfalse);
	a.Definir(12,signtrue);
	a.Definir(14,signtrue);
	a.Definir(19,signfalse);
	ASSERT(!a.EsVacio());
	ASSERT(a.Definido(5));
	ASSERT(a.Definido(6));
	ASSERT(a.Definido(3));
	ASSERT(a.Definido(7));
	ASSERT(a.Definido(11));
	ASSERT(a.Definido(12));
	ASSERT(a.Definido(14));
	ASSERT(a.Definido(15));
	ASSERT(a.Definido(19));
	ASSERT_EQ(a.CantClaves(), 9);
	a.Borrar(11);
	ASSERT(!a.Definido(11));
	ASSERT(a.Definido(5));
	ASSERT(a.Definido(6));
	ASSERT(a.Definido(3));
	ASSERT(a.Definido(7));
	ASSERT(a.Definido(12));
	ASSERT(a.Definido(14));
	ASSERT(a.Definido(15));
	ASSERT(a.Definido(19));
	ASSERT_EQ(a.CantClaves(), 8);
	a.Borrar(5);
	a.Borrar(6);
	a.Borrar(3);
	a.Borrar(7);
	a.Borrar(12);
	a.Borrar(15);
	a.Borrar(14);
	a.Borrar(19);
	ASSERT(!a.Definido(5));
	ASSERT(!a.Definido(6));
	ASSERT(!a.Definido(3));
	ASSERT(!a.Definido(7));
	ASSERT(!a.Definido(11));
	ASSERT(!a.Definido(12));
	ASSERT(!a.Definido(14));
	ASSERT(!a.Definido(15));
	ASSERT(!a.Definido(19));
	ASSERT_EQ(a.CantClaves(), 0);
	ASSERT(a.EsVacio());


//            __,- 20 -,__             |                   
//           /            \            |                  
//         10             30           |                   
//       /   \         /     \         |            
//      5     15      25      35       |                  
//     / \    / \    /  \    /  \      |                 
//    1   7  12 19  22  27  31  38     |                   
//	
// Caso: borro 1ro 31, 2do 7, 3ro 5, 4to 25 

	a.Definir(20,signtrue);
	a.Definir(10,signtrue);
	a.Definir(30,signtrue);
	a.Definir(5,signtrue);
	a.Definir(15,signtrue);
	a.Definir(25,signtrue);
	a.Definir(35,signtrue);
	a.Definir(1,signtrue);
	a.Definir(7,signtrue);
	a.Definir(12,signtrue);
	a.Definir(19,signtrue);
	a.Definir(22,signtrue);
	a.Definir(27,signtrue);
	a.Definir(31,signtrue);
	a.Definir(38,signtrue);
	ASSERT(!a.EsVacio());
	ASSERT(a.Definido(20));
	ASSERT(a.Definido(10));
	ASSERT(a.Definido(30));
	ASSERT(a.Definido(5));
	ASSERT(a.Definido(15));
	ASSERT(a.Definido(25));
	ASSERT(a.Definido(35));
	ASSERT(a.Definido(1));
	ASSERT(a.Definido(7));
	ASSERT(a.Definido(12));
	ASSERT(a.Definido(19));
	ASSERT(a.Definido(22));
	ASSERT(a.Definido(27));
	ASSERT(a.Definido(31));
	ASSERT(a.Definido(38));
	ASSERT_EQ(a.CantClaves(), 15);
	a.Borrar(31);
	ASSERT(a.Definido(20));
	ASSERT(a.Definido(10));
	ASSERT(a.Definido(30));
	ASSERT(a.Definido(5));
	ASSERT(a.Definido(15));
	ASSERT(a.Definido(25));
	ASSERT(a.Definido(35));
	ASSERT(a.Definido(1));
	ASSERT(a.Definido(7));
	ASSERT(a.Definido(12));
	ASSERT(a.Definido(19));
	ASSERT(a.Definido(22));
	ASSERT(a.Definido(27));
	ASSERT(!a.Definido(31));
	ASSERT(a.Definido(38));
	ASSERT_EQ(a.CantClaves(), 14);
	a.Borrar(7);
	ASSERT(a.Definido(20));
	ASSERT(a.Definido(10));
	ASSERT(a.Definido(30));
	ASSERT(a.Definido(5));
	ASSERT(a.Definido(15));
	ASSERT(a.Definido(25));
	ASSERT(a.Definido(35));
	ASSERT(a.Definido(1));
	ASSERT(!a.Definido(7));
	ASSERT(a.Definido(12));
	ASSERT(a.Definido(19));
	ASSERT(a.Definido(22));
	ASSERT(a.Definido(27));
	ASSERT(!a.Definido(31));
	ASSERT(a.Definido(38));
	ASSERT_EQ(a.CantClaves(), 13);
	a.Borrar(5);
	ASSERT(a.Definido(20));
	ASSERT(a.Definido(10));
	ASSERT(a.Definido(30));
	ASSERT(!a.Definido(5));
	ASSERT(a.Definido(15));
	ASSERT(a.Definido(25));
	ASSERT(a.Definido(35));
	ASSERT(a.Definido(1));
	ASSERT(!a.Definido(7));
	ASSERT(a.Definido(12));
	ASSERT(a.Definido(19));
	ASSERT(a.Definido(22));
	ASSERT(a.Definido(27));
	ASSERT(!a.Definido(31));
	ASSERT(a.Definido(38));
	ASSERT_EQ(a.CantClaves(), 12);
	a.Borrar(25);
	ASSERT(a.Definido(20));
	ASSERT(a.Definido(10));
	ASSERT(a.Definido(30));
	ASSERT(!a.Definido(5));
	ASSERT(a.Definido(15));
	ASSERT(!a.Definido(25));
	ASSERT(a.Definido(35));
	ASSERT(a.Definido(1));
	ASSERT(!a.Definido(7));
	ASSERT(a.Definido(12));
	ASSERT(a.Definido(19));
	ASSERT(a.Definido(22));
	ASSERT(a.Definido(27));
	ASSERT(!a.Definido(31));
	ASSERT(a.Definido(38));
	ASSERT_EQ(a.CantClaves(), 11);
	a.Borrar(20);
	a.Borrar(10);
	a.Borrar(30);
	a.Borrar(15);
	a.Borrar(35);
	a.Borrar(1);
	a.Borrar(12);
	a.Borrar(19);
	a.Borrar(22);
	a.Borrar(27);
	a.Borrar(38);
	ASSERT_EQ(a.CantClaves(), 0);
	ASSERT(a.EsVacio());


//            __,- 20 -,__             |                   
//           /            \            |                  
//         10             30           |                   
//       /   \         /     \         |            
//      5     15      25      35       |                  
//     / \    / \    /  \    /  \      |                 
//    1   7  12 19  22  27  31  38     |                   
//	
// Caso: borro 1ro 10 y 2do 30 

	a.Definir(20,signtrue);
	a.Definir(10,signtrue);
	a.Definir(30,signtrue);
	a.Definir(5,signtrue);
	a.Definir(15,signtrue);
	a.Definir(25,signtrue);
	a.Definir(35,signtrue);
	a.Definir(1,signtrue);
	a.Definir(7,signtrue);
	a.Definir(12,signtrue);
	a.Definir(19,signtrue);
	a.Definir(22,signtrue);
	a.Definir(27,signtrue);
	a.Definir(31,signtrue);
	a.Definir(38,signtrue);
	ASSERT(!a.EsVacio());
	ASSERT(a.Definido(20));
	ASSERT(a.Definido(10));
	ASSERT(a.Definido(30));
	ASSERT(a.Definido(5));
	ASSERT(a.Definido(15));
	ASSERT(a.Definido(25));
	ASSERT(a.Definido(35));
	ASSERT(a.Definido(1));
	ASSERT(a.Definido(7));
	ASSERT(a.Definido(12));
	ASSERT(a.Definido(19));
	ASSERT(a.Definido(22));
	ASSERT(a.Definido(27));
	ASSERT(a.Definido(31));
	ASSERT(a.Definido(38));
	ASSERT_EQ(a.CantClaves(), 15);
	a.Borrar(30);
	ASSERT(a.Definido(20));
	ASSERT(a.Definido(10));
	ASSERT(!a.Definido(30));
	ASSERT(a.Definido(5));
	ASSERT(a.Definido(15));
	ASSERT(a.Definido(25));
	ASSERT(a.Definido(35));
	ASSERT(a.Definido(1));
	ASSERT(a.Definido(7));
	ASSERT(a.Definido(12));
	ASSERT(a.Definido(19));
	ASSERT(a.Definido(22));
	ASSERT(a.Definido(27));
	ASSERT(a.Definido(31));
	ASSERT(a.Definido(38));
	ASSERT_EQ(a.CantClaves(), 14);
	a.Borrar(10);
	ASSERT(a.Definido(20));
	ASSERT(!a.Definido(10));
	ASSERT(!a.Definido(30));
	ASSERT(a.Definido(5));
	ASSERT(a.Definido(15));
	ASSERT(a.Definido(25));
	ASSERT(a.Definido(35));
	ASSERT(a.Definido(1));
	ASSERT(a.Definido(7));
	ASSERT(a.Definido(12));
	ASSERT(a.Definido(19));
	ASSERT(a.Definido(22));
	ASSERT(a.Definido(27));
	ASSERT(a.Definido(31));
	ASSERT(a.Definido(38));
	ASSERT_EQ(a.CantClaves(), 13);
	a.Borrar(20);
	a.Borrar(5);
	a.Borrar(25);
	a.Borrar(15);
	a.Borrar(35);
	a.Borrar(1);
	a.Borrar(7);
	a.Borrar(12);
	a.Borrar(19);
	a.Borrar(22);
	a.Borrar(27);
	a.Borrar(31);
	a.Borrar(38);
	ASSERT_EQ(a.CantClaves(), 0);
	ASSERT(a.EsVacio());


//            __,- 20 -,__             |                   
//           /            \            |                  
//         10             30           |                   
//        /                 \          |            
//       5                   35        |                  
//      / \                 /  \       |                 
//     1   7               31  38      |                   
//	
// Caso: borro 1ro 10 y 2do 30 

	a.Definir(20,signtrue);
	a.Definir(10,signtrue);
	a.Definir(30,signtrue);
	a.Definir(5,signtrue);
	a.Definir(35,signtrue);
	a.Definir(1,signtrue);
	a.Definir(7,signtrue);
	a.Definir(31,signtrue);
	a.Definir(38,signtrue);
	ASSERT(!a.EsVacio());
	ASSERT(a.Definido(20));
	ASSERT(a.Definido(10));
	ASSERT(a.Definido(30));
	ASSERT(a.Definido(5));
	ASSERT(a.Definido(35));
	ASSERT(a.Definido(1));
	ASSERT(a.Definido(7));
	ASSERT(a.Definido(31));
	ASSERT(a.Definido(38));
	ASSERT_EQ(a.CantClaves(), 9);
	a.Borrar(30);
	ASSERT(a.Definido(20));
	ASSERT(a.Definido(10));
	ASSERT(!a.Definido(30));
	ASSERT(a.Definido(5));
	ASSERT(a.Definido(35));
	ASSERT(a.Definido(1));
	ASSERT(a.Definido(7));
	ASSERT(a.Definido(31));
	ASSERT(a.Definido(38));
	ASSERT_EQ(a.CantClaves(), 8);
	a.Borrar(10);
	ASSERT(a.Definido(20));
	ASSERT(!a.Definido(10));
	ASSERT(!a.Definido(30));
	ASSERT(a.Definido(5));
	ASSERT(a.Definido(35));
	ASSERT(a.Definido(1));
	ASSERT(a.Definido(7));
	ASSERT(a.Definido(31));
	ASSERT(a.Definido(38));
	ASSERT_EQ(a.CantClaves(), 7);
	a.Borrar(20);
	a.Borrar(5);
	a.Borrar(35);
	a.Borrar(1);
	a.Borrar(7);
	a.Borrar(31);
	a.Borrar(38);
	ASSERT_EQ(a.CantClaves(), 0);
	ASSERT(a.EsVacio());


//            __,- 20 -,__             |                   
//           /            \            |                  
//         10             30           |                   
//           \            /            |            
//           15          25            |                  
//           / \        /  \           |                 
//          12 19      22   27         |                   
//	
// Caso: borro 1ro 10 y 2do 30 

	a.Definir(20,signtrue);
	a.Definir(10,signtrue);
	a.Definir(30,signtrue);
	a.Definir(15,signtrue);
	a.Definir(25,signtrue);
	a.Definir(12,signtrue);
	a.Definir(19,signtrue);
	a.Definir(22,signtrue);
	a.Definir(27,signtrue);
	ASSERT(!a.EsVacio());
	ASSERT(a.Definido(20));
	ASSERT(a.Definido(10));
	ASSERT(a.Definido(30));
	ASSERT(a.Definido(15));
	ASSERT(a.Definido(25));
	ASSERT(a.Definido(12));
	ASSERT(a.Definido(19));
	ASSERT(a.Definido(22));
	ASSERT(a.Definido(27));
	ASSERT_EQ(a.CantClaves(), 9);
	a.Borrar(10);
	ASSERT(a.Definido(20));
	ASSERT(!a.Definido(10));
	ASSERT(a.Definido(30));
	ASSERT(a.Definido(15));
	ASSERT(a.Definido(25));
	ASSERT(a.Definido(12));
	ASSERT(a.Definido(19));
	ASSERT(a.Definido(22));
	ASSERT(a.Definido(27));
	ASSERT_EQ(a.CantClaves(), 8);
	a.Borrar(30);
	ASSERT(a.Definido(20));
	ASSERT(!a.Definido(10));
	ASSERT(!a.Definido(30));
	ASSERT(a.Definido(15));
	ASSERT(a.Definido(25));
	ASSERT(a.Definido(12));
	ASSERT(a.Definido(19));
	ASSERT(a.Definido(22));
	ASSERT(a.Definido(27));
	ASSERT_EQ(a.CantClaves(), 7);
	a.Borrar(20);
	a.Borrar(15);
	a.Borrar(25);
	a.Borrar(12);
	a.Borrar(19);
	a.Borrar(22);
	a.Borrar(27);
	ASSERT_EQ(a.CantClaves(), 0);
	ASSERT(a.EsVacio());
}

void test_ClaveMinima_ClaveMaxima(){
	Nat sign;
	diccNat<Nat> a;

//	Caso: 		  5					X
//              	     ->
//             		     ->
//

	sign = 5;
	a.Definir(5, sign);
	ASSERT_EQ(a.ClaveMinima(), 5);
	ASSERT_EQ(a.ClaveMaxima(), 5);
	a.Borrar(5);


//	Caso:    5            3               X
//          /      ->            ->
//         3       ->            ->
//

	sign = 5;
	a.Definir(5, sign);
	ASSERT_EQ(a.ClaveMinima(), 5);
	ASSERT_EQ(a.ClaveMaxima(), 5);
	sign = 3;
	a.Definir(3, sign);
	ASSERT_EQ(a.ClaveMinima(), 3);
	ASSERT_EQ(a.ClaveMaxima(), 5);
	a.Borrar(5);
	ASSERT_EQ(a.ClaveMinima(), 3);
	ASSERT_EQ(a.ClaveMaxima(), 3);
	a.Borrar(3);


//	Caso:     5            5               X
//           /      ->            ->
//          3       ->            ->
//

	sign = 5;
	a.Definir(5, sign);
	ASSERT_EQ(a.ClaveMinima(), 5);
	ASSERT_EQ(a.ClaveMaxima(), 5);
	sign = 3;
	a.Definir(3, sign);
	ASSERT_EQ(a.ClaveMinima(), 3);
	ASSERT_EQ(a.ClaveMaxima(), 5);
	a.Borrar(3);
	ASSERT_EQ(a.ClaveMinima(), 5);
	ASSERT_EQ(a.ClaveMaxima(), 5);
	a.Borrar(5);



//	Caso:   5              5               X
//           \     ->             ->
//            6    ->             ->
//

	sign = 5;
	a.Definir(5, sign);
	ASSERT_EQ(a.ClaveMinima(), 5);
	ASSERT_EQ(a.ClaveMaxima(), 5);
	sign = 6;
	a.Definir(6, sign);
	ASSERT_EQ(a.ClaveMinima(), 5);
	ASSERT_EQ(a.ClaveMaxima(), 6);
	a.Borrar(6);
	ASSERT_EQ(a.ClaveMinima(), 5);
	ASSERT_EQ(a.ClaveMaxima(), 5);
	a.Borrar(5);



//	Caso:   5            6               X
//           \    ->            ->
//            6   ->            ->
//

	sign = 5;
	a.Definir(5, sign);
	ASSERT_EQ(a.ClaveMinima(), 5);
	ASSERT_EQ(a.ClaveMaxima(), 5);
	sign = 6;
	a.Definir(6, sign);
	ASSERT_EQ(a.ClaveMinima(), 5);
	ASSERT_EQ(a.ClaveMaxima(), 6);
	a.Borrar(5);
	ASSERT_EQ(a.ClaveMinima(), 6);
	ASSERT_EQ(a.ClaveMaxima(), 6);
	a.Borrar(6);



//	Caso:    5            6               6               X
//          / \    ->    /        ->             ->
//         3   6   ->   3         ->             ->
//

	sign = 5;
	a.Definir(5, sign);
	ASSERT_EQ(a.ClaveMinima(), 5);
	ASSERT_EQ(a.ClaveMaxima(), 5);
	sign = 6;
	a.Definir(6, sign);
	ASSERT_EQ(a.ClaveMinima(), 5);
	ASSERT_EQ(a.ClaveMaxima(), 6);
	sign = 3;
	a.Definir(3, sign);
	ASSERT_EQ(a.ClaveMinima(), 3);
	ASSERT_EQ(a.ClaveMaxima(), 6);
	a.Borrar(5);
	ASSERT_EQ(a.ClaveMinima(), 3);
	ASSERT_EQ(a.ClaveMaxima(), 6);
	a.Borrar(3);
	ASSERT_EQ(a.ClaveMinima(), 6);
	ASSERT_EQ(a.ClaveMaxima(), 6);
	a.Borrar(6);



//	Caso:    5            5               6               X
//          / \    ->      \      ->             ->
//         3   6   ->       6     ->             ->
//

	sign = 5;
	a.Definir(5, sign);
	ASSERT_EQ(a.ClaveMinima(), 5);
	ASSERT_EQ(a.ClaveMaxima(), 5);
	sign = 6;
	a.Definir(6, sign);
	ASSERT_EQ(a.ClaveMinima(), 5);
	ASSERT_EQ(a.ClaveMaxima(), 6);
	sign = 3;
	a.Definir(3, sign);
	ASSERT_EQ(a.ClaveMinima(), 3);
	ASSERT_EQ(a.ClaveMaxima(), 6);
	a.Borrar(3);
	ASSERT_EQ(a.ClaveMinima(), 5);
	ASSERT_EQ(a.ClaveMaxima(), 6);
	a.Borrar(5);
	ASSERT_EQ(a.ClaveMinima(), 6);
	ASSERT_EQ(a.ClaveMaxima(), 6);
	a.Borrar(6);



//  Caso:       5            5               3               X
//	           / \    ->    /        ->             ->
//	          3   6   ->   3         ->             ->
//	 

	sign = 5;
	a.Definir(5, sign);
	ASSERT_EQ(a.ClaveMinima(), 5);
	ASSERT_EQ(a.ClaveMaxima(), 5);
	sign = 6;
	a.Definir(6, sign);
	ASSERT_EQ(a.ClaveMinima(), 5);
	ASSERT_EQ(a.ClaveMaxima(), 6);
	sign = 3;
	a.Definir(3, sign);
	ASSERT_EQ(a.ClaveMinima(), 3);
	ASSERT_EQ(a.ClaveMaxima(), 6);
	a.Borrar(6);
	ASSERT_EQ(a.ClaveMinima(), 3);
	ASSERT_EQ(a.ClaveMaxima(), 5);
	a.Borrar(5);
	ASSERT_EQ(a.ClaveMinima(), 3);
	ASSERT_EQ(a.ClaveMaxima(), 3);
	a.Borrar(3);
	


//  Caso:       5              3                            
//	           /      ->      / \       -> BORRO ARBOL
//	          3       ->     1   4      -> CON CASO ANTERIOR 
//	         / \      ->                ->
//	        1   4     ->                -> 
//	 

	sign = 5;
	a.Definir(5, sign);
	ASSERT_EQ(a.ClaveMinima(), 5);
	ASSERT_EQ(a.ClaveMaxima(), 5);
	sign = 3;
	a.Definir(3, sign);
	ASSERT_EQ(a.ClaveMinima(), 3);
	ASSERT_EQ(a.ClaveMaxima(), 5);
	sign = 1;
	a.Definir(1, sign);
	ASSERT_EQ(a.ClaveMinima(), 1);
	ASSERT_EQ(a.ClaveMaxima(), 5);
	sign = 4;
	a.Definir(4, sign);
	ASSERT_EQ(a.ClaveMinima(), 1);
	ASSERT_EQ(a.ClaveMaxima(), 5);
	a.Borrar(5);
	ASSERT_EQ(a.ClaveMinima(), 1);
	ASSERT_EQ(a.ClaveMaxima(), 4);
	a.Borrar(3);
	ASSERT_EQ(a.ClaveMinima(), 1);
	ASSERT_EQ(a.ClaveMaxima(), 4);
	a.Borrar(1);
	ASSERT_EQ(a.ClaveMinima(), 4);
	ASSERT_EQ(a.ClaveMaxima(), 4);
	a.Borrar(4);


//   Caso:      5                 10                         
//	             \        ->      / \      -> BORRO ARBOL
//	              10      ->     6   13    -> CON CASO ANTERIOR 
//	              / \     ->               ->
//	             6   13   ->               -> 
//	 

	sign = 5;
	a.Definir(5, sign);
	ASSERT_EQ(a.ClaveMinima(), 5);
	ASSERT_EQ(a.ClaveMaxima(), 5);
	sign = 10;
	a.Definir(10, sign);
	ASSERT_EQ(a.ClaveMinima(), 5);
	ASSERT_EQ(a.ClaveMaxima(), 10);
	sign = 13;
	a.Definir(13, sign);
	ASSERT_EQ(a.ClaveMinima(), 5);
	ASSERT_EQ(a.ClaveMaxima(), 13);
	sign = 6;
	a.Definir(6, sign);
	ASSERT_EQ(a.ClaveMinima(), 5);
	ASSERT_EQ(a.ClaveMaxima(), 13);
	a.Borrar(5);
	ASSERT_EQ(a.ClaveMinima(), 6);
	ASSERT_EQ(a.ClaveMaxima(), 13);
	a.Borrar(13);
	ASSERT_EQ(a.ClaveMinima(), 6);
	ASSERT_EQ(a.ClaveMaxima(), 10);
	a.Borrar(10);
	ASSERT_EQ(a.ClaveMinima(), 6);
	ASSERT_EQ(a.ClaveMaxima(), 6);
	a.Borrar(6);
	

//  Caso:       9                     11                       
//	          /   \         ->       /   \        -> BORRO ARBOL
//	         5     15       ->      5     15      -> CON CASO ANTERIOR 
//	        / \    /  \     ->     / \    / \     ->
//	       3   7  12  19    ->    3   7  12  19   -> 
//	          /  /  \       ->       /     \      ->
//	         6  11  14      ->      6       14    ->
//	 
	sign = 9;
	a.Definir(9, sign);
	ASSERT_EQ(a.ClaveMinima(), 9);
	ASSERT_EQ(a.ClaveMaxima(), 9);
	sign = 5;
	a.Definir(5, sign);
	ASSERT_EQ(a.ClaveMinima(), 5);
	ASSERT_EQ(a.ClaveMaxima(), 9);
	sign = 15;
	a.Definir(15, sign);
	ASSERT_EQ(a.ClaveMinima(), 5);
	ASSERT_EQ(a.ClaveMaxima(), 15);
	sign = 7;
	a.Definir(7, sign);
	ASSERT_EQ(a.ClaveMinima(), 5);
	ASSERT_EQ(a.ClaveMaxima(), 15);
	sign = 6;
	a.Definir(6, sign);
	ASSERT_EQ(a.ClaveMinima(), 5);
	ASSERT_EQ(a.ClaveMaxima(), 15);
	sign = 3;
	a.Definir(3, sign);
	ASSERT_EQ(a.ClaveMinima(), 3);
	ASSERT_EQ(a.ClaveMaxima(), 15);
	sign = 12;
	a.Definir(12, sign);
	ASSERT_EQ(a.ClaveMinima(), 3);
	ASSERT_EQ(a.ClaveMaxima(), 15);
	sign = 11;
	a.Definir(11, sign);
	ASSERT_EQ(a.ClaveMinima(), 3);
	ASSERT_EQ(a.ClaveMaxima(), 15);
	sign = 14;
	a.Definir(14, sign);
	ASSERT_EQ(a.ClaveMinima(), 3);
	ASSERT_EQ(a.ClaveMaxima(), 15);
	sign = 19;
	a.Definir(19, sign);
	ASSERT_EQ(a.ClaveMinima(), 3);
	ASSERT_EQ(a.ClaveMaxima(), 19);
	a.Borrar(9);
	ASSERT_EQ(a.ClaveMinima(), 3);
	ASSERT_EQ(a.ClaveMaxima(), 19);
	a.Borrar(6);
	ASSERT_EQ(a.ClaveMinima(), 3);
	ASSERT_EQ(a.ClaveMaxima(), 19);
	a.Borrar(3);
	ASSERT_EQ(a.ClaveMinima(), 5);
	ASSERT_EQ(a.ClaveMaxima(), 19);
	a.Borrar(7);
	ASSERT_EQ(a.ClaveMinima(), 5);
	ASSERT_EQ(a.ClaveMaxima(), 19);
	a.Borrar(11);
	ASSERT_EQ(a.ClaveMinima(), 5);
	ASSERT_EQ(a.ClaveMaxima(), 19);
	a.Borrar(12);
	ASSERT_EQ(a.ClaveMinima(), 5);
	ASSERT_EQ(a.ClaveMaxima(), 19);
	a.Borrar(15);
	ASSERT_EQ(a.ClaveMinima(), 5);
	ASSERT_EQ(a.ClaveMaxima(), 19);
	a.Borrar(14);
	ASSERT_EQ(a.ClaveMinima(), 5);
	ASSERT_EQ(a.ClaveMaxima(), 19);
	a.Borrar(19);
	ASSERT_EQ(a.ClaveMinima(), 5);
	ASSERT_EQ(a.ClaveMaxima(), 5);
	a.Borrar(5);
	


//   Caso:       11                  12     
//	            /   \        ->     /   \        -> BORRO ARBOL
//	           5     15      ->    5     15      -> CON CASO ANTERIOR 
//	          / \    / \     ->   / \    / \     ->
//	         3   7  12  19   ->  3   7  14  19   -> 
//	            /     \      ->     /            ->
//	           6       14    ->    6             ->
//	 

	sign = 11;
	a.Definir(11, sign);
	ASSERT_EQ(a.ClaveMinima(), 11);
	ASSERT_EQ(a.ClaveMaxima(), 11);
	sign = 5;
	a.Definir(5, sign);
	ASSERT_EQ(a.ClaveMinima(), 5);
	ASSERT_EQ(a.ClaveMaxima(), 11);
	sign = 15;
	a.Definir(15, sign);
	ASSERT_EQ(a.ClaveMinima(), 5);
	ASSERT_EQ(a.ClaveMaxima(), 15);
	sign = 7;
	a.Definir(7, sign);
	ASSERT_EQ(a.ClaveMinima(), 5);
	ASSERT_EQ(a.ClaveMaxima(), 15);
	sign = 6;
	a.Definir(6, sign);
	ASSERT_EQ(a.ClaveMinima(), 5);
	ASSERT_EQ(a.ClaveMaxima(), 15);
	sign = 3;
	a.Definir(3, sign);
	ASSERT_EQ(a.ClaveMinima(), 3);
	ASSERT_EQ(a.ClaveMaxima(), 15);
	sign = 12;
	a.Definir(12, sign);
	ASSERT_EQ(a.ClaveMinima(), 3);
	ASSERT_EQ(a.ClaveMaxima(), 15);
	sign = 14;
	a.Definir(14, sign);
	ASSERT_EQ(a.ClaveMinima(), 3);
	ASSERT_EQ(a.ClaveMaxima(), 15);
	sign = 19;
	a.Definir(19, sign);
	ASSERT_EQ(a.ClaveMinima(), 3);
	ASSERT_EQ(a.ClaveMaxima(), 19);
	
	a.Borrar(11);
	ASSERT_EQ(a.ClaveMinima(), 3);
	ASSERT_EQ(a.ClaveMaxima(), 19);
	a.Borrar(5);
	ASSERT_EQ(a.ClaveMinima(), 3);
	ASSERT_EQ(a.ClaveMaxima(), 19);
	a.Borrar(6);
	ASSERT_EQ(a.ClaveMinima(), 3);
	ASSERT_EQ(a.ClaveMaxima(), 19);
	a.Borrar(3);
	ASSERT_EQ(a.ClaveMinima(), 7);
	ASSERT_EQ(a.ClaveMaxima(), 19);
	a.Borrar(7);
	ASSERT_EQ(a.ClaveMinima(), 12);
	ASSERT_EQ(a.ClaveMaxima(), 19);
	a.Borrar(12);
	ASSERT_EQ(a.ClaveMinima(), 14);
	ASSERT_EQ(a.ClaveMaxima(), 19);
	a.Borrar(15);
	ASSERT_EQ(a.ClaveMinima(), 14);
	ASSERT_EQ(a.ClaveMaxima(), 19);
	a.Borrar(14);
	ASSERT_EQ(a.ClaveMinima(), 19);
	ASSERT_EQ(a.ClaveMaxima(), 19);
	a.Borrar(19);
	


//            __,- 20 -,__             |                   
//           /            \            |                  
//         10             30           |                   
//       /   \         /     \         |            
//      5     15      25      35       |                  
//     / \    / \    /  \    /  \      |                 
//    1   7  12 19  22  27  31  38     |                   
//	
// Caso: borro 1ro 31, 2do 7, 3ro 5, 4to 25 

	sign = 20;
	a.Definir(20, sign);
	ASSERT_EQ(a.ClaveMinima(), 20);
	ASSERT_EQ(a.ClaveMaxima(), 20);
	sign = 10;
	a.Definir(10, sign);
	ASSERT_EQ(a.ClaveMinima(), 10);
	ASSERT_EQ(a.ClaveMaxima(), 20);
	sign = 30;
	a.Definir(30, sign);
	ASSERT_EQ(a.ClaveMinima(), 10);
	ASSERT_EQ(a.ClaveMaxima(), 30);
	sign = 5;
	a.Definir(5, sign);
	ASSERT_EQ(a.ClaveMinima(), 5);
	ASSERT_EQ(a.ClaveMaxima(), 30);
	sign = 15;
	a.Definir(15, sign);
	ASSERT_EQ(a.ClaveMinima(), 5);
	ASSERT_EQ(a.ClaveMaxima(), 30);
	sign = 25;
	a.Definir(25, sign);
	ASSERT_EQ(a.ClaveMinima(), 5);
	ASSERT_EQ(a.ClaveMaxima(), 30);
	sign = 35;
	a.Definir(35, sign);
	ASSERT_EQ(a.ClaveMinima(), 5);
	ASSERT_EQ(a.ClaveMaxima(), 35);
	sign = 1;
	a.Definir(1, sign);
	ASSERT_EQ(a.ClaveMinima(), 1);
	ASSERT_EQ(a.ClaveMaxima(), 35);
	sign = 7;
	a.Definir(7, sign);
	ASSERT_EQ(a.ClaveMinima(), 1);
	ASSERT_EQ(a.ClaveMaxima(), 35);
	sign = 12;
	a.Definir(12, sign);
	ASSERT_EQ(a.ClaveMinima(), 1);
	ASSERT_EQ(a.ClaveMaxima(), 35);
	sign = 19;
	a.Definir(19, sign);
	ASSERT_EQ(a.ClaveMinima(), 1);
	ASSERT_EQ(a.ClaveMaxima(), 35);
	sign = 22;
	a.Definir(22, sign);
	ASSERT_EQ(a.ClaveMinima(), 1);
	ASSERT_EQ(a.ClaveMaxima(), 35);
	sign = 27;
	a.Definir(27, sign);
	ASSERT_EQ(a.ClaveMinima(), 1);
	ASSERT_EQ(a.ClaveMaxima(), 35);
	sign = 31;
	a.Definir(31, sign);
	ASSERT_EQ(a.ClaveMinima(), 1);
	ASSERT_EQ(a.ClaveMaxima(), 35);
	sign = 38;
	a.Definir(38, sign);
	ASSERT_EQ(a.ClaveMinima(), 1);
	ASSERT_EQ(a.ClaveMaxima(), 38);
	a.Borrar(31);
	ASSERT_EQ(a.ClaveMinima(), 1);
	ASSERT_EQ(a.ClaveMaxima(), 38);
	a.Borrar(7);
	ASSERT_EQ(a.ClaveMinima(), 1);
	ASSERT_EQ(a.ClaveMaxima(), 38);
	a.Borrar(5);
	ASSERT_EQ(a.ClaveMinima(), 1);
	ASSERT_EQ(a.ClaveMaxima(), 38);
	a.Borrar(25);
	ASSERT_EQ(a.ClaveMinima(), 1);
	ASSERT_EQ(a.ClaveMaxima(), 38);
	a.Borrar(20);
	ASSERT_EQ(a.ClaveMinima(), 1);
	ASSERT_EQ(a.ClaveMaxima(), 38);
	a.Borrar(10);
	ASSERT_EQ(a.ClaveMinima(), 1);
	ASSERT_EQ(a.ClaveMaxima(), 38);
	a.Borrar(30);
	ASSERT_EQ(a.ClaveMinima(), 1);
	ASSERT_EQ(a.ClaveMaxima(), 38);
	a.Borrar(15);
	ASSERT_EQ(a.ClaveMinima(), 1);
	ASSERT_EQ(a.ClaveMaxima(), 38);
	a.Borrar(35);
	ASSERT_EQ(a.ClaveMinima(), 1);
	ASSERT_EQ(a.ClaveMaxima(), 38);
	a.Borrar(1);
	ASSERT_EQ(a.ClaveMinima(), 12);
	ASSERT_EQ(a.ClaveMaxima(), 38);
	a.Borrar(12);
	ASSERT_EQ(a.ClaveMinima(), 19);
	ASSERT_EQ(a.ClaveMaxima(), 38);
	a.Borrar(19);
	ASSERT_EQ(a.ClaveMinima(), 22);
	ASSERT_EQ(a.ClaveMaxima(), 38);
	a.Borrar(22);
	ASSERT_EQ(a.ClaveMinima(), 27);
	ASSERT_EQ(a.ClaveMaxima(), 38);
	a.Borrar(27);
	ASSERT_EQ(a.ClaveMinima(), 38);
	ASSERT_EQ(a.ClaveMaxima(), 38);
	a.Borrar(38);
	


//            __,- 20 -,__             |                   
//           /            \            |                  
//         10             30           |                   
//       /   \         /     \         |            
//      5     15      25      35       |                  
//     / \    / \    /  \    /  \      |                 
//    1   7  12 19  22  27  31  38     |                   
//	
// Caso: borro 1ro 10 y 2do 30 

	sign = 20;
	a.Definir(20,sign);
	ASSERT_EQ(a.ClaveMinima(), 20);
	ASSERT_EQ(a.ClaveMaxima(), 20);
	sign = 10;
	a.Definir(10,sign);
	ASSERT_EQ(a.ClaveMinima(), 10);
	ASSERT_EQ(a.ClaveMaxima(), 20);
	sign = 30;
	a.Definir(30,sign);
	ASSERT_EQ(a.ClaveMinima(), 10);
	ASSERT_EQ(a.ClaveMaxima(), 30);
	sign = 5;
	a.Definir(5,sign);
	ASSERT_EQ(a.ClaveMinima(), 5);
	ASSERT_EQ(a.ClaveMaxima(), 30);
	sign = 15;
	a.Definir(15,sign);
	ASSERT_EQ(a.ClaveMinima(), 5);
	ASSERT_EQ(a.ClaveMaxima(), 30);
	sign = 25;
	a.Definir(25,sign);
	ASSERT_EQ(a.ClaveMinima(), 5);
	ASSERT_EQ(a.ClaveMaxima(), 30);
	sign = 35;
	a.Definir(35,sign);
	ASSERT_EQ(a.ClaveMinima(), 5);
	ASSERT_EQ(a.ClaveMaxima(), 35);
	sign = 1;
	a.Definir(1,sign);
	ASSERT_EQ(a.ClaveMinima(), 1);
	ASSERT_EQ(a.ClaveMaxima(), 35);
	sign = 7;
	a.Definir(7,sign);
	ASSERT_EQ(a.ClaveMinima(), 1);
	ASSERT_EQ(a.ClaveMaxima(), 35);
	sign = 12;
	a.Definir(12,sign);
	ASSERT_EQ(a.ClaveMinima(), 1);
	ASSERT_EQ(a.ClaveMaxima(), 35);
	sign = 19;
	a.Definir(19,sign);
	ASSERT_EQ(a.ClaveMinima(), 1);
	ASSERT_EQ(a.ClaveMaxima(), 35);
	sign = 22;
	a.Definir(22,sign);
	ASSERT_EQ(a.ClaveMinima(), 1);
	ASSERT_EQ(a.ClaveMaxima(), 35);
	sign = 27;
	a.Definir(27,sign);
	ASSERT_EQ(a.ClaveMinima(), 1);
	ASSERT_EQ(a.ClaveMaxima(), 35);
	sign = 31;
	a.Definir(31,sign);
	ASSERT_EQ(a.ClaveMinima(), 1);
	ASSERT_EQ(a.ClaveMaxima(), 35);
	sign = 38;
	a.Definir(38,sign);
	ASSERT_EQ(a.ClaveMinima(), 1);
	ASSERT_EQ(a.ClaveMaxima(), 38);
	a.Borrar(30);
	ASSERT_EQ(a.ClaveMinima(), 1);
	ASSERT_EQ(a.ClaveMaxima(), 38);
	a.Borrar(10);
	ASSERT_EQ(a.ClaveMinima(), 1);
	ASSERT_EQ(a.ClaveMaxima(), 38);
	a.Borrar(20);
	ASSERT_EQ(a.ClaveMinima(), 1);
	ASSERT_EQ(a.ClaveMaxima(), 38);
	a.Borrar(5);
	ASSERT_EQ(a.ClaveMinima(), 1);
	ASSERT_EQ(a.ClaveMaxima(), 38);
	a.Borrar(25);
	ASSERT_EQ(a.ClaveMinima(), 1);
	ASSERT_EQ(a.ClaveMaxima(), 38);
	a.Borrar(15);
	ASSERT_EQ(a.ClaveMinima(), 1);
	ASSERT_EQ(a.ClaveMaxima(), 38);
	a.Borrar(35);
	ASSERT_EQ(a.ClaveMinima(), 1);
	ASSERT_EQ(a.ClaveMaxima(), 38);
	a.Borrar(1);
	ASSERT_EQ(a.ClaveMinima(), 7);
	ASSERT_EQ(a.ClaveMaxima(), 38);
	a.Borrar(7);
	ASSERT_EQ(a.ClaveMinima(), 12);
	ASSERT_EQ(a.ClaveMaxima(), 38);
	a.Borrar(12);
	ASSERT_EQ(a.ClaveMinima(), 19);
	ASSERT_EQ(a.ClaveMaxima(), 38);
	a.Borrar(19);
	ASSERT_EQ(a.ClaveMinima(), 22);
	ASSERT_EQ(a.ClaveMaxima(), 38);
	a.Borrar(22);
	ASSERT_EQ(a.ClaveMinima(), 27);
	ASSERT_EQ(a.ClaveMaxima(), 38);
	a.Borrar(27);
	ASSERT_EQ(a.ClaveMinima(), 31);
	ASSERT_EQ(a.ClaveMaxima(), 38);
	a.Borrar(31);
	ASSERT_EQ(a.ClaveMinima(), 38);
	ASSERT_EQ(a.ClaveMaxima(), 38);
	a.Borrar(38);
	


//            __,- 20 -,__             |                   
//           /            \            |                  
//         10             30           |                   
//        /                 \          |            
//       5                   35        |                  
//      / \                 /  \       |                 
//     1   7               31  38      |                   
//	
// Caso: borro 1ro 10 y 2do 30 

	sign = 20;
	a.Definir(20, sign);
	ASSERT_EQ(a.ClaveMinima(), 20);
	ASSERT_EQ(a.ClaveMaxima(), 20);
	sign = 10;
	a.Definir(10, sign);
	ASSERT_EQ(a.ClaveMinima(), 10);
	ASSERT_EQ(a.ClaveMaxima(), 20);
	sign = 30;
	a.Definir(30, sign);
	ASSERT_EQ(a.ClaveMinima(), 10);
	ASSERT_EQ(a.ClaveMaxima(), 30);
	sign = 5;
	a.Definir(5, sign);
	ASSERT_EQ(a.ClaveMinima(), 5);
	ASSERT_EQ(a.ClaveMaxima(), 30);
	sign = 35;
	a.Definir(35, sign);
	ASSERT_EQ(a.ClaveMinima(), 5);
	ASSERT_EQ(a.ClaveMaxima(), 35);
	sign = 1;
	a.Definir(1, sign);
	ASSERT_EQ(a.ClaveMinima(), 1);
	ASSERT_EQ(a.ClaveMaxima(), 35);
	sign = 7;
	a.Definir(7, sign);
	ASSERT_EQ(a.ClaveMinima(), 1);
	ASSERT_EQ(a.ClaveMaxima(), 35);
	sign = 31;
	a.Definir(31, sign);
	ASSERT_EQ(a.ClaveMinima(), 1);
	ASSERT_EQ(a.ClaveMaxima(), 35);
	sign = 38;
	a.Definir(38, sign);
	ASSERT_EQ(a.ClaveMinima(), 1);
	ASSERT_EQ(a.ClaveMaxima(), 38);
	a.Borrar(30);
	ASSERT_EQ(a.ClaveMinima(), 1);
	ASSERT_EQ(a.ClaveMaxima(), 38);
	a.Borrar(10);
	ASSERT_EQ(a.ClaveMinima(), 1);
	ASSERT_EQ(a.ClaveMaxima(), 38);
	a.Borrar(20);
	ASSERT_EQ(a.ClaveMinima(), 1);
	ASSERT_EQ(a.ClaveMaxima(), 38);
	a.Borrar(5);
	ASSERT_EQ(a.ClaveMinima(), 1);
	ASSERT_EQ(a.ClaveMaxima(), 38);
	a.Borrar(35);
	ASSERT_EQ(a.ClaveMinima(), 1);
	ASSERT_EQ(a.ClaveMaxima(), 38);
	a.Borrar(1);
	ASSERT_EQ(a.ClaveMinima(), 7);
	ASSERT_EQ(a.ClaveMaxima(), 38);
	a.Borrar(7);
	ASSERT_EQ(a.ClaveMinima(), 31);
	ASSERT_EQ(a.ClaveMaxima(), 38);
	a.Borrar(31);
	ASSERT_EQ(a.ClaveMinima(), 38);
	ASSERT_EQ(a.ClaveMaxima(), 38);
	a.Borrar(38);



//            __,- 20 -,__             |                   
//           /            \            |                  
//         10             30           |                   
//           \            /            |            
//           15          25            |                  
//           / \        /  \           |                 
//          12 19      22   27         |                   
//	
// Caso: borro 1ro 10 y 2do 30 

	sign = 20;
	a.Definir(20, sign);
	ASSERT_EQ(a.ClaveMinima(), 20);
	ASSERT_EQ(a.ClaveMaxima(), 20);
	sign = 10;
	a.Definir(10, sign);
	ASSERT_EQ(a.ClaveMinima(), 10);
	ASSERT_EQ(a.ClaveMaxima(), 20);
	sign = 30;
	a.Definir(30, sign);
	ASSERT_EQ(a.ClaveMinima(), 10);
	ASSERT_EQ(a.ClaveMaxima(), 30);
	sign = 15;
	a.Definir(15, sign);
	ASSERT_EQ(a.ClaveMinima(), 10);
	ASSERT_EQ(a.ClaveMaxima(), 30);
	sign = 25;
	a.Definir(25, sign);
	ASSERT_EQ(a.ClaveMinima(), 10);
	ASSERT_EQ(a.ClaveMaxima(), 30);
	sign = 12;
	a.Definir(12, sign);
	ASSERT_EQ(a.ClaveMinima(), 10);
	ASSERT_EQ(a.ClaveMaxima(), 30);
	sign = 19;
	a.Definir(19, sign);
	ASSERT_EQ(a.ClaveMinima(), 10);
	ASSERT_EQ(a.ClaveMaxima(), 30);
	sign = 22;
	a.Definir(22, sign);
	ASSERT_EQ(a.ClaveMinima(), 10);
	ASSERT_EQ(a.ClaveMaxima(), 30);
	sign = 27;
	a.Definir(27, sign);
	ASSERT_EQ(a.ClaveMinima(), 10);
	ASSERT_EQ(a.ClaveMaxima(), 30);
	a.Borrar(10);
	ASSERT_EQ(a.ClaveMinima(), 12);
	ASSERT_EQ(a.ClaveMaxima(), 30);
	a.Borrar(30);
	ASSERT_EQ(a.ClaveMinima(), 12);
	ASSERT_EQ(a.ClaveMaxima(), 27);
	a.Borrar(20);
	ASSERT_EQ(a.ClaveMinima(), 12);
	ASSERT_EQ(a.ClaveMaxima(), 27);
	a.Borrar(15);
	ASSERT_EQ(a.ClaveMinima(), 12);
	ASSERT_EQ(a.ClaveMaxima(), 27);
	a.Borrar(25);
	ASSERT_EQ(a.ClaveMinima(), 12);
	ASSERT_EQ(a.ClaveMaxima(), 27);
	a.Borrar(12);
	ASSERT_EQ(a.ClaveMinima(), 19);
	ASSERT_EQ(a.ClaveMaxima(), 27);
	a.Borrar(19);
	ASSERT_EQ(a.ClaveMinima(), 22);
	ASSERT_EQ(a.ClaveMaxima(), 27);
	a.Borrar(22);
	ASSERT_EQ(a.ClaveMinima(), 27);
	ASSERT_EQ(a.ClaveMaxima(), 27);
	a.Borrar(27);
}

void test_significado_modifica(){
	diccNat<int> a;
	int sign = 10;
	a.Definir(5, sign);
	a.Definir(3, sign);
	a.Definir(7, sign);
	a.Definir(1, sign);
	a.Definir(4, sign);
	a.Definir(6 ,sign);
	a.Definir(9, sign);

	a.Significado(5) += 10;
	a.Significado(3) += 10;
	a.Significado(7) += 10;
	a.Significado(1) += 10;
	a.Significado(4) += 10;
	a.Significado(6) += 10;
	a.Significado(9) += 10;

	ASSERT_EQ(a.Significado(5), 20);
	ASSERT_EQ(a.Significado(3), 20);
	ASSERT_EQ(a.Significado(7), 20);
	ASSERT_EQ(a.Significado(1), 20);
	ASSERT_EQ(a.Significado(4), 20);
	ASSERT_EQ(a.Significado(6), 20);
	ASSERT_EQ(a.Significado(9), 20);
}


void testDiccNat(int argc, char **argv) {

	if(!testSelect(argc,argv,"diccnat"))
		return;

	cout << "Test de diccnat" << endl;
	cout << "-----------------------------" << endl;

	RUN_TEST(test_constructor_vacio);
	RUN_TEST(test_definir_definido_significado);
	RUN_TEST(test_borrar);
	RUN_TEST(test_ClaveMinima_ClaveMaxima);
	RUN_TEST(test_significado_modifica);

	cout << "-----------------------------" << endl;

}

