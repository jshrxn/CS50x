// A program that simulates an election by the Tideman voting method.

#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
bool can_reach(int current, int target);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // Search through all the candidates to find the one
    // whose name matches the name provided by the voter.
    for (int i = 0; i < candidate_count; i++)
    {
        // strcmp return 0 when two strings are identical.
        if (strcmp(candidates[i], name) == 0)
        {
            // Store the candidates index at the voter's specified ranking position.
            ranks[rank] = i;

            // The candidates is found, so the vote is valid.
            return true;
        }
    }
    // No candidate matched the provided name.
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Compare each candidate with every candidate ranked below them.
    // Since higher-ranked candidates are preferred over lower-ranked candidates,
    // each comparison represents one pairwise preference.
    for (int i = 0; i < candidate_count; i++)
    {
        // Start at i + 1 so we only compare candidates below
        // the current candidate in the voter's ranking.
        for (int j = i + 1; j < candidate_count; j++)
        {
            // ranks[i] is preferred over ranks[j] by this voter.
            int winner = ranks[i];
            int loser = ranks[j];

            // Record one additional voter who prefers winner over loser.
            preferences[winner][loser]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // Compare every unique pair of candidates.
    // Starting j at i + 1 prevents checking the same matchup twice.
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            // If more voters prefer i over j, i wins this matchup.
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            // Otherwise, if more voters prefer j over i, j wins the matchup.
            else if (preferences[j][i] > preferences[i][j])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
            // If the counts are equal, the matchup is a tie and is not added to pairs[].
        }
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // Compare each pair with the pairs that come after it.
    // Stronger victories should be placed earlier in the array.
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = i + 1; j < pair_count; j++)
        {
            // The strength of a pair is the number of voters
            // who preferred its winner over its loser.
            int strength_i = preferences[pairs[i].winner][pairs[i].loser];
            int strength_j = preferences[pairs[j].winner][pairs[j].loser];

            // If the later pair is stronger, swap the two pairs.
            if (strength_j > strength_i)
            {
                // Use a temporary pair so neither pair is lost during the swap.
                pair temp = pairs[i];
                pairs[i] = pairs[j];
                pairs[j] = temp;
            }
        }
    }
    return;
}

// Checks whether we can travel from "current" to "target"
// through the arrows that have already been locked.
bool can_reach(int current, int target)
{
    // If we've reached the target, a path exists.
    if (current == target)
    {
        return true;
    }

    // Check every candidate that "current" points to.
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[current][i])
        {
            // Follow that arrow and keep searching
            if (can_reach(i, target))
            {
                return true;
            }
        }
    }
    // No path to target was found.
    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // Pairs are already sorted from strongest to weakest.
    for (int i = 0; i < pair_count; i++)
    {
        int winner = pairs[i].winner;
        int loser = pairs[i].loser;

        // Before adding winner -> loser, check whether loser can already reach winner.
        // If yes, loser -> ... -> winner -> loser would create a cycle.
        if (!can_reach(loser, winner))
        {
            // Safe: add the arrow.
            locked[winner][loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // Check every candidate
    for (int i = 0; i < candidate_count; i++)
    {
        // Assume this candidate has no incoming arrows
        bool has_incoming_edge = false;

        // Check whether any candidates points to candidate i
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                // Someone points to candidate i, so i cannot be the winner
                has_incoming_edge = true;
                break;
            }
        }

        // If nobody points to candidate i, this candidate is the winner.
        if (!has_incoming_edge)
        {
            printf("%s\n", candidates[i]);
            return;
        }
    }
}
