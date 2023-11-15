# Resolution-Refutation

## To run the code
## Windows
Open command prompt 
## Linux
Open linux command line
## Clone the repository
```bash
git clone https://github.com/Ris-code/Resolution-Refutation.git
```

# Resolution Refutation and CNF Conversion in C++

This C++ program implements the resolution refutation method for propositional logic. It includes both uninformed and informed (greedy) search strategies. It also converts a given proposition into Conjunctive Normal Form (CNF).

## Classes

- `cnf`: This class is used to convert a given proposition into Conjunctive Normal Form (CNF).
- `ResolutionRefutation`: This class is used to perform resolution refutation on a given knowledge base (KB).

## Functions

- `separateClauses`: This function separates a given conjunction into individual clauses.
- `convert_to_cnf`: This function converts a given proposition into CNF using the `cnf` class.
- `uninformed_search`: This function performs an uninformed search on a given KB using the `ResolutionRefutation` class.
- `informed_greedy_search`: This function performs an informed greedy search on a given KB using the `ResolutionRefutation` class.

## Usage

1. Compile the program with a C++ compiler.
2. Run the program. When prompted, enter the number of propositions and queries, followed by each proposition and query.
3. The program will then print out the results of the uninformed and informed searches.

## Example TestCase
``` 
4 0
P|(Q&(R>T))
P>R
Q>T
Q>(R=T)
R 
```
```
2 0
p>q
q>r
r>p

```
- `OR`: |
- `AND`: &
- `NOT`: !
- `IMPLICATION`: >
- `IFF (bidirectional)`: =
- `OPENING BRACKET`: (
- `CLOSING BRACKET`: )
