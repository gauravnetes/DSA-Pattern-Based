# LC 253: Meeting Rooms II (Minimum Meeting Rooms)

**Pattern Trigger:** "Max concurrent events", "Booking calendars", "Minimum rooms needed" = Line Sweep (1D).

**State Variables:**
* `map<int, int> mp` (Chronological timeline of events)
* `overlaps` (Running sum of currently active meetings)
* `maxOverlap` (Peak concurrent meetings observed)

**The "Aha!" Pivot:**
Stop looking at intervals as two connected points. Break them into independent *events* on a timeline. 
* A `start` time adds demand for a room: `mp[start]++`.
* An `end` time frees a room: `mp[end]--`.
Because `std::map` is implemented as a Red-Black Tree in C++, it automatically sorts these timestamps chronologically. By iterating through the map and accumulating the values into `overlaps`, you track the exact number of rooms in use at any given moment.

**Edge Cases to Memorize:**
* **Back-to-back meetings:** If meeting A ends at `10` and meeting B starts at `10`, the `map` aggregates them at key `10` as `+1 - 1 = 0`. The running sum won't artificially spike, which perfectly handles the logic that back-to-back meetings can share the same room.

**Complexity:**
* **Time:** $\mathcal{O}(N \log N)$ (Inserting $2N$ elements into a balanced BST).
* **Space:** $\mathcal{O}(N)$ to store the unique timestamps in the map.