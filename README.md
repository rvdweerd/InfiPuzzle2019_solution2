# InfiPuzzle2019_solution2
2e oplossing (C++), nu met Dijkstra

In deze oplossing construeren we nog steeds alle mogelijke routes, maar dit keer in een graph data structure (Nodes en directede Arcs). Op de volledige graph passen we Dijkstra toe. Mooie als demo, maar niet heel efficient, het is in principe niet nodig eerst de hele graph te vullen. Dit laat ik zien in oplossing #3.

Zie comments in main() </br>
[Screenshot van oplossing](/InfiPuzzle2019_solution2_output.png)

Mijn andere  oplossingen:
1. Bouwt tree met alle unieke routes (nodes met ontkoppelde vertakkingen); zeer kostbaar maar ontsluit alle mogelijke info ->
[repo oplossing 1](https://github.com/rvdweerd/InfiPuzzle2019.git)
3. Bouwt graph (nodes en directed arcs) terwijl we Dijkstra toepassen. Dit is de meest efficiente toepassing want alleen het strikt nodige werk wordt gedaan. -> [repo oplossing 3](https://github.com/rvdweerd/InfiPuzzle2019_solution3.git)
