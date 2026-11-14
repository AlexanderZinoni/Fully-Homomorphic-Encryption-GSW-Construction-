# Homomorphic Encryption: The GSW construction

This is a basic and not secure implementation of GSW as described in the lecture notes [[1]](#1).

## Description of the algorithm 

The security of GSW relies on the LWE assumption with parameters $(m,n,q,\chi)$.Here
$\ell = (n+1)\log q$.


- **Key Gen** $(1^n) \rightarrow s \in \mathbb{Z}_q^{n+1}$

  - Sample a random vector $s'$ from $\mathbb{Z}_q^n$.
  - Return the vector $s$ with $n+1$ corrdinates by adding a 1 as last coordinate to $s'$. 

- **Enc** $(s \in \mathbb{Z}_q^{n+1},\ \mu \in \mathbb{Z}_2) \rightarrow C \in \mathbb{Z}_q^{\ell \times (n+1)}$

  - Sample a random matrix $A$ from  $\mathbb{Z}_q^{\ell \times n}$.
  - Sample an error vector $e$ in $\chi^\ell$, where $\chi$ is the error distribution. In this implementation, I rely on the Central Limit Theorem to implement this.
  - Build:
    $$B = (A \parallel As' + e) \in \mathbb{Z}_q^{\ell \times (n+1)}$$, where $||$ means that we add $As'+e$ as an extra column at the end of $A$.
  - Let $G \in \mathbb{Z}_q^{\ell \times (n+1)}$ be a fixed public gadget matrix.
  - Output:
    $$C = B + \mu \cdot G$$

- **Dec** $(s,C) \rightarrow \mu$

  - Compute the vector:
    $$v = C \cdot s = (B+\mu G)s = Bs + \mu Gs$$
  - Output "0" if the magnitude of each entry of $v$ is small (i.e., less than $q/4$). Otherwise, output "1".

  - We have:
  $$C \cdot s = ((A \parallel As' + e) + \mu G)(-s'\;1)
  = -As' + As' + e + \mu Gs
  = e + \mu Gs$$
  which is of small magnitude if s = 0.
  $e + \mu Gs$ is called the decryption invariant.

## What I still need to do

- [ ] Add Homomorphic oprations (sum and product).
- [ ] Increase variable size (32bit -> 64bit).
- [ ] Use something more cryptographically secure than `rand()`.

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


## References
<a id="1">[1]</a> 
Alexandra Henzinger (2026). 
[Fully Homomorphic Encryption (part I)](https://65610.csail.mit.edu/2026/lec/l09-fhe1.pdf).
MIT - 6.5610. Lecture 9 (March 4, 2026)
