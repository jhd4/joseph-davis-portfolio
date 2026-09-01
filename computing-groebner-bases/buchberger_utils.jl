using Oscar
include("multivariable_division_utils.jl")

function lcm_of_leading_monomials(f::T, g::T, ord::MonomialOrdering) where T<: MPolyRingElem
    @assert parent(f) == parent(g) "$f and $g do not belong to the same ring"
    @assert ord.R == parent(f) "$ord does not belong to the same ring as $f and $g"

    R = ord.R
    lm_f = leading_monomial(f, ordering = ord)
    lm_g = leading_monomial(g, ordering = ord)
    output_lcm = one(R)
    for x_i in gens(R)
        f_deg = degree(lm_f, x_i)
        g_deg = degree(lm_g, x_i)
        output_lcm *= x_i^max(f_deg, g_deg)
    end

    return output_lcm
end

function syzygy_polynomial(f::T, g::T, ord::MonomialOrdering) where T <: MPolyRingElem
    @assert parent(f) == parent(g) "$f and $g do not belong to the same ring"
    @assert ord.R == parent(f) "$ord does not belong to the same ring as $f and $g"
    x_gamma = lcm_of_leading_monomials(f, g, ord)
    lt_f = leading_term(f, ordering = ord)
    lt_g = leading_term(g, ordering = ord)
    f_divides, _ = divides(x_gamma, lt_f)
    @assert f_divides "Bad LCM generation, $lt_f does not divide $x_gamma"
    g_divides, _ = divides(x_gamma, lt_g)
    @assert g_divides "Bad LCM generation, $lt_g does not divide $x_gamma"
    f_multiplier = divexact(x_gamma, lt_f)
    g_multiplier = divexact(x_gamma, lt_g)

    return (f_multiplier * f) - (g_multiplier * g)
end

function groebner_basis_buchberger_algorithm(F::Vector{T}, ord::MonomialOrdering) where T <: MPolyRingElem
    @assert all(parent(f) == parent(F[1]) for f in F) "All polynomials must belong to the same ring"
    @assert ord.R == parent(F[1]) "Ordering must belong to the same ring"

    G = deepcopy(F)
    g_grew = true
    while g_grew
        g_grew = false
        for i in eachindex(G)
            for j in eachindex(G)[i+1:end]
                _, r = multivariable_division(syzygy_polynomial(G[i], G[j], ord), G, ord)
                if !is_zero(r)
                    push!(G, r)
                    g_grew = true
                end
            end
        end
    end

    return G
end

function reduced_groebner_basis_buchberger_algorithm(F::Vector{T}, ord::MonomialOrdering) where T <: MPolyRingElem
    G = groebner_basis_buchberger_algorithm(F, ord)

    for index in eachindex(G)[end:-1:1]
        g = G[index]
        if length(G) > 1
            lt_G_slash_g = T[]
            for i in eachindex(G)
                if i != index
                    push!(lt_G_slash_g, leading_monomial(G[i], ordering = ord))
                end
            end

            lt_g = leading_term(g, ordering = ord)
            _, r_lt = multivariable_division(lt_g, lt_G_slash_g, ord)
            if is_zero(r_lt)
                deleteat!(G, index)
            else
                subtraction_polynomial = zero(ord.R)
                for t in terms(g - lt_g)
                    _, r = multivariable_division(t, lt_G_slash_g, ord)
                    if is_zero(r)
                        subtraction_polynomial += t
                    end
                end
                g -= subtraction_polynomial
                g = divexact(g, leading_coefficient(g, ordering = ord))
                G[index] = g
            end
        else
            G[index] = divexact(g, leading_coefficient(g, ordering = ord))
        end
        
    end

    return G
end

