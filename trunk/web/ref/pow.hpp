#ifndef POW_HPP
#define POW_HPP

namespace dz {

/* @class pow
   @description Computes the <i>N</i>th power of a given number
   without loops if the power is known at compile time.

   <p>The following example shows what the assembler code might
   look like if no loop unroll techniques are used and the power is
   computed at compile time. A loop is created which is passed
   through eight times. Not only loops are expensive on
   contemporary processors but we have eight multiplications
   as well.
<table><tr><td valign=top>
<pre>
int y = rand();
int r = y;
for (int i = 2; i <= 8; ++i, r *= y);     
</pre>
</td><td>
<pre>
    movl    $2, %ecx
.LVL4:
    movl    %eax, %edx
.LVL5:
    .p2align 4,,7
.L13:
.LBB81:
    .loc 1 9 0
    addl    $1, %ecx
    imull   %eax, %edx
    cmpl    $9, %ecx
    jne .L13
</pre>
</td></tr></table>
   </p>
   <p>If the power is already known at compile time loop unroll
   cann be used to compute the power without loops.
<table><tr><td valign=top>
<pre>
int x = pow<8>::compute(rand());
</pre>
</td><td>
<pre>
    call    rand
    .loc 1 10 0
    movl    $_ZSt4cout, (%esp)
    imull   %eax, %eax
    imull   %eax, %eax
    imull   %eax, %eax
    movl    %eax, 4(%esp)
    call    _ZNSolsEi
</pre>
</td></tr></table>

   @example
int x = pow<8>::compute(rand());
std::cout << x << std::endl;

   @exdescription
   Computes the eighth power of a random number usually with just three multiplications.

   @1 N @2 The exponent. @3

   @see copy_n
*/
template<unsigned N>
class pow
{
public:
  /* @mem Computes the <i>N</i>th power of t. */
  template<typename T>
  static T
  compute(const T& t)
  { return t * pow<N - 1>::compute(t); }
};

template<>
class pow<1>
{
public:
  template<typename T>
  static T
  compute(const T& t)
  { return t; }
};

template<>
class pow<0>
{
public:
  template<typename T>
  static T
  compute(const T& t)
  { return static_cast<T>(1); }
};

};

#endif
