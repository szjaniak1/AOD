using JuMP
using HiGHS
using Printf

import JSON

data = JSON.parse("""
{
    "firmy": {
        "Firma1": {"capacity": 275000},
        "Firma2": {"capacity": 550000},
        "Firma3": {"capacity": 660000}
    },
    "lotniska": {
        "Lotnisko1": {"demand": 110000},
        "Lotnisko2": {"demand": 220000},
        "Lotnisko3": {"demand": 330000},
        "Lotnisko4": {"demand": 440000}
    },
    "ceny": {
        "Firma1 => Lotnisko1": 10,
        "Firma1 => Lotnisko2": 10,
        "Firma1 => Lotnisko3": 9,
        "Firma1 => Lotnisko4": 11,
        "Firma2 => Lotnisko1": 7,
        "Firma2 => Lotnisko2": 11,
        "Firma2 => Lotnisko3": 12,
        "Firma2 => Lotnisko4": 13,
        "Firma3 => Lotnisko1": 8,
        "Firma3 => Lotnisko2": 14,
        "Firma3 => Lotnisko3": 4,
        "Firma3 => Lotnisko4": 9
    }
}
""")

Firmy = keys(data["firmy"])
Lotniska = keys(data["lotniska"])
koszty(Firmy::String, Lotniska::String) = data["ceny"]["$(Firmy) => $(Lotniska)"]

model = Model(HiGHS.Optimizer)
@variable(model, x[Firmy, Lotniska] >= 0)
@constraint(model, [f in Firmy], sum(x[f, l] for l in Lotniska) <= data["firmy"][f]["capacity"])
@constraint(model, [l in Lotniska], sum(x[f, l] for f in Firmy) >= data["lotniska"][l]["demand"])
@objective(model, Min, sum(koszty(f, l) * x[f, l] for f in Firmy, l in Lotniska));

optimize!(model)
solution_summary(model)

@printf "\npierwszy podpunkt:\n\n"
@printf "minimalny koszt: %d\n\n" objective_value(model)

@printf "drugi podpunkt:\n\n"


for f in Firmy
    @printf "%s dostarczyla %d galonow paliwa\n" f value(sum(x[f, l] for l in Lotniska))
    if value(sum(x[f, l] for l in Lotniska)) > 0.0
        global S = 0
        S += 1
    end
end

if S == length(collect(Firmy))
    @printf "wszystkie firmy dostarczaja paliwo\n\n"
else
    @printf "nie wszystkie firmy dostarczaja paliwo\n\n"
end

S = 0

@printf "trzeci podpunkt:\n\n"

for f in Firmy
    if value(sum(x[f, l] for l in Lotniska)) == data["firmy"][f]["capacity"]
        @printf "%s wyczerpala mozliwosci dostaw paliwa\n" f
    end
end

@printf "\n"

for f in Firmy, l in Lotniska
    @printf "%s => %s: %d\n" f l value(x[f, l])
end
