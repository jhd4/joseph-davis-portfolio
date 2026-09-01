using Oscar

function multivariable_division(input_dividend::T, divisors::Vector{T}, ord::MonomialOrdering) where T <: MPolyRingElem
    @assert all(parent(divisor) == parent(divisors[1]) for divisor in divisors) "All polynomials must belong to the same ring"
    @assert ord.R == parent(divisors[1]) "Ordering must belong to the same ring"

    R = ord.R

    dividend = deepcopy(input_dividend)

    remainder = zero(R)
    quotients = Dict{T, T}()

    while !is_zero(dividend)
        divisor_found = false
        for divisor in divisors
            ok, _ = divides(leading_monomial(dividend, ordering = ord), leading_monomial(divisor, ordering = ord))
            if ok
                q = divexact(leading_term(dividend, ordering = ord), leading_term(divisor, ordering = ord))
                quotients[divisor] =  get(quotients, divisor, zero(R)) + q
                dividend -= q * divisor
                divisor_found = true
                break
            end
        end
        if !divisor_found
            remainder += leading_term(dividend, ordering = ord)
            dividend -= leading_term(dividend, ordering = ord)
        end
    end

    return quotients, remainder
end

function format_product_nicely(dividend::T, quotients::Dict{T, T}, remainder::T) where T<: MPolyRingElem
    output_string = ""
    output_string *= "$dividend = "
    
    for (k, v) in quotients
        output_string *= "($v) * ($k) + "
    end

    output_string *= "($remainder)"
    return output_string
end