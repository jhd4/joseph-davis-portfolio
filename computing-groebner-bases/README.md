# Computing Gröbner Bases in Julia

A Julia package for computational commutative algebra implementing multivariate polynomial division, S-polynomial (syzygy) generation, and Buchberger's algorithm to compute Gröbner bases and reduced Gröbner bases.

---

## Architecture & Implementation

The library provides algorithm implementations built on top of the Oscar.jl computer algebra framework:

* **`multivariable_division_utils.jl`**: Implements multivariate polynomial division across arbitrary monomial orderings (`MonomialOrdering`), returning quotient dictionaries and remainders.
* **`buchberger_utils.jl`**: Contains core commutative algebra algorithms:
  * `lcm_of_leading_monomials`: Computes entry-wise maximum exponent vectors over generator sets.
  * `syzygy_polynomial`: Generates S-polynomials $S(f, g) = \frac{x^\gamma}{\text{lt}(f)} f - \frac{x^\gamma}{\text{lt}(g)} g$.
  * `groebner_basis_buchberger_algorithm`: Constructs generator sets closed under S-polynomial reduction.
  * `reduced_groebner_basis_buchberger_algorithm`: Eliminates redundant generators and normalizes leading coefficients to produce unique reduced Gröbner bases.

---

## Verification & Testing

* **`test_funcs.jl`**: Automated test suite that verifies custom implementation results against Oscar.jl's native engine. Compares generated ideal representations to assert equality:
  $$\langle G_{\text{custom}} \rangle = \langle G_{\text{oscar}} \rangle$$

---

## Usage Example

```julia
using Oscar
include("multivariable_division_utils.jl")
include("buchberger_utils.jl")
include("test_funcs.jl")

R, (x, y) = polynomial_ring(QQ, ["x", "y"])
ord = lex(R)

f1 = x^3 - 2*x*y
f2 = x^2*y - 2*y^2 + x

F = [f1, f2]

# Compute reduced Gröbner basis
G_reduced = reduced_groebner_basis_buchberger_algorithm(F, ord)

# Test against Oscar native engine
test_reduced_groebner_basis(F, ord)