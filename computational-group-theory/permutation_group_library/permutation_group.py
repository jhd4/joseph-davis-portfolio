from .permutation import Permutation

class Permutation_Group:
    def __init__(this, generator_list):
        this.members = list(generator_list)
        this.generate_group()
        this.order = len(this.members)

    def generate_group(this):
        i = 0
        while i < len(this.members):
            operand_A = this.members[i]
            for operand_B in this.members:
                for new_permutation in [operand_A * operand_B, operand_B * operand_A]:
                    if not this.contains(new_permutation):
                        this.members.append(new_permutation)
            i += 1

    def contains(this, perm):
        for member in this.members:
            if member == perm:
                return True
        return False

    def __str__(this):
        output = f"Permutation Group of Order {this.order}:\n"
        for member in this.members:
            output += member.__str__() + "\n"
        return output
    
    def __eq__(this, other):
        if this.order != other.order:
            return False
        for this_member in this.members:
            if not other.contains(this_member):
                return False
        return True

if __name__ == "__main__":
    p1 = Permutation([[1, 2]])
    p2 = Permutation([[3, 4]])
    # p3 = Permutation([[4, 5]])
    # print(f"{p1} o {p2} == {p1 * p2}")
    # print(f"{p2} o {p1} == {p2 * p1}")

    group = Permutation_Group([p1, p2])
    print(group)
