# Homomorphic Encryption: The GSW construction

This is a basic and not secure implementation of GSW as described in the lecture notes [[1]](#1).

## Project Structure
    .
    ├── include/    # Header files (.h)
    ├── src/        # Source files (.c)
    ├── makefile    # for compilation
    └── README.md

## Compilation and Running

Compile the project using `make`:

    make

and execute it with :

    ./main matrix.txt

To remove the generated executable and object files:

    make clean

## Output Example

There currently are 3 functions:

- `KeyGen`: Takes a security parameter an integer `n` and returns a randomly sampled vector `s`.

- `Enc`: Takes a secret key `s` and a bit `b` and returns the ciphertext: a matrix `C`.  

- `Dec`: Takes a secret key `s` and a ciphtertext `C` and recovers the encrrypted bit `b`.

I have also added a `check_correctness` function which I use in `Enc`. It verifies that the decryption invariant holds before returning a ciphertext to make sure it is correct.

      Input Matrix: 
      [[1,-1,3]
      [1,0,5]
      [1,2,6]]

      LLL reduced matrix:
      [[0,1,-1]
      [1,0,0]
      [0,1,2]]

      Reduction Successful!


In the case where the reduction is unsuccessful, the program specifies whether the basis is not size-reduced or the Lovasz condition does not hold.

## Decription of the algorithm


The security of GSW relies on the LWE assumption with parameters $(m,n,q,\chi)$ and
$\ell = (n+1)\log q$.


- **Key Gen** $(1^n) \rightarrow s \in \mathbb{Z}_q^{n+1}$

  - Sample a random vector $s' \xleftarrow{R} \mathbb{Z}_q^n$.
  - Output:
    $$s = \begin{pmatrix} -s' \\ 1 \end{pmatrix} \in \mathbb{Z}_q^{n+1}$$






## What I still need to do

- [ ] Add Homomorphic oprations (sum and product).
- [ ] Increase variable size (32bit -> 64bit).
- [ ] Use something more cryptographically secure than `rand()`.


## References
<a id="1">[1]</a> 
Alexandra Henzinger (2026). 
[Fully Homomorphic Encryption (part I)](https://65610.csail.mit.edu/2026/lec/l09-fhe1.pdf).
MIT - 6.5610. Lecture 9 (March 4, 2026)
