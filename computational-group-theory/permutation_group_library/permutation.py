from .cycle import Cycle

class Permutation:
    def __init__(this, cycle_list):
        this.cycles = []
        for cycle in cycle_list:
            if isinstance(cycle, Cycle):
                this.cycles.append(cycle)
            else:
                this.cycles.append(Cycle(cycle))
        this.cycles = sorted(this.cycles, key=lambda c: c.min_element)
        if len(this.cycles) == 0:
            this.cycles.append(Cycle([1]))
        this.max_element = this.get_max()
        this.min_element = this.get_min()

    def get_max(this):
        current_max_element = 0
        for cycle in this.cycles:
            current_max_element = max(cycle.max_element, current_max_element)
        return current_max_element  
    
    def get_min(this):
        current_min_element = this.cycles[0].min_element
        for cycle in this.cycles:
            current_min_element = min(cycle.min_element, current_min_element)
        return current_min_element

    def __str__(this):
        output = ""
        if len(this.cycles) > 0:
            for cycle in this.cycles:
                output += cycle.__str__()
        else:
            output += "(IDENTITY_PERMUTATION)"
        return output

    def __call__(this, n):
        for cycle in this.cycles:
            output = cycle(n)
            if output != n:
                return output
        return n

    def __repr__(this):
        return this.__str__()

    def __mul__(this, other):
        processed_elements = set()
        # start at the lowest element of other
        mul_min = min(this.min_element, other.min_element)
        mul_max = max(this.max_element, other.max_element)
        output_cycles = []
        for i in range(mul_min, mul_max + 1):
            if i in processed_elements:
                continue
            else:
                current_cycle = [i]
                processed_elements.add(i)
                n = this(other(i))
                while(n != i):
                    processed_elements.add(n)
                    current_cycle.append(n)
                    n = this(other(n))
                if len(current_cycle) > 1:
                    output_cycles.append(Cycle(current_cycle))
        return Permutation(output_cycles)
    
    def __eq__(this, other):
        eq_min = min(this.min_element, other.min_element)
        eq_max = max(this.max_element, other.max_element)
        for i in range(eq_min, eq_max + 1):
            if this(i) != other(i):
                return False
        return True


if __name__ == "__main__":
    base_cycle = Cycle([1, 2, 3, 4, 5, 6, 7])

    base_permutation = Permutation([base_cycle])
    next_permutation = base_permutation
    for i in range(7):
        new_permutation = base_permutation * next_permutation
        print(f"{base_permutation} o {next_permutation} = {new_permutation}")
        next_permutation = new_permutation

    perm_A = Permutation([[1], [2, 3, 5]])
    perm_B = Permutation([[20, 6], [2, 3, 5]])

    print(f"{perm_A} == {perm_B} is {perm_A == perm_B}")