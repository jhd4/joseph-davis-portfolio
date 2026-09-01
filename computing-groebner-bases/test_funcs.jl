using Oscar
include("multivariable_division_utils.jl")
include("buchberger_utils.jl")


function test_groebner_basis(F::Vector{T}, ord::MonomialOrdering) where T <: MPolyRingElem
    @assert all(parent(f) == parent(F[1]) for f in F) "All polynomials must belong to the same ring"
    @assert ord.R == parent(F[1]) "Ordering must belong to the same ring"
    R = ord.R
    G = groebner_basis_buchberger_algorithm(F, ord)
    G_oscar = collect(groebner_basis(ideal(R, F), ordering = ord))
    println("G: $G")
    println("G_oscar: $G_oscar")
    println("Equality: $(ideal(R, G) == ideal(R, G_oscar))")
end

function test_reduced_groebner_basis(F::Vector{T}, ord::MonomialOrdering) where T <: MPolyRingElem
    @assert all(parent(f) == parent(F[1]) for f in F) "All polynomials must belong to the same ring"
    @assert ord.R == parent(F[1]) "Ordering must belong to the same ring"
    R = ord.R
    G = reduced_groebner_basis_buchberger_algorithm(F, ord)
    G_oscar = collect(groebner_basis(ideal(R, F), ordering = ord))
    println("G: $G")
    println("G_oscar: $G_oscar")
    println("Equality: $(ideal(R, G) == ideal(R, G_oscar))")
end