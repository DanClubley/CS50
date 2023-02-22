
// CS50 Week 3 - Algorithms : Tideman
// Dan Clubley 22 Feb 2023
// Vote on candidates using the Tideman method. Takes into account overall ranking of candidates.
// List candidates as command line arguments
// Prompt user for amount of voters
// Prompt user for each voters' vote
// Return winning candidate(s)

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
}
pair;

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
void lock_pairs(void);
void print_winner(void);
bool cycle_check(int loser_index, int start_position);

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

        /*
        printf("Ranks: ");
        for (int k = 0; k < candidate_count; k++)
        {
            printf("%i ", ranks[k]);
        }
        printf("\n");
        */

        record_preferences(ranks);
        printf("\n");
    }

    /*
    printf("Preferences:\n");
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("%i ", preferences[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    */

    add_pairs();

    /*
    for (int i = 0; i < pair_count; i++)
    {
        printf("Winner: %i Loser: %i Votes: %i\n", pairs[i].winner, pairs[i].loser, preferences[pairs[i].winner][pairs[i].loser]);
    }
    printf("\n");
    */

    sort_pairs();

    /*
    for (int i = 0; i < pair_count; i++)
    {
        printf("Winner: %i Loser: %i Votes: %i\n", pairs[i].winner, pairs[i].loser, preferences[pairs[i].winner][pairs[i].loser]);
    }
    printf("\n");
    */

    lock_pairs();

    /*
    printf("Locked:\n");
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("%i ", locked[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    */

    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[j][i] > preferences[i][j])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int to_sort[pair_count];
    int swap_count;
    int temp;
    pair temp_pair;

    for (int i = 0; i < pair_count + 1; i++)
    {
        to_sort[i] = preferences[pairs[i].winner][pairs[i].loser];
    }

    for (int i = 0; i < pair_count; i++)
    {
        swap_count = 0;
        for (int j = 0; j < pair_count - 1; j++)
        {
            if (to_sort[j] < to_sort[j + 1])
            {
                temp = to_sort[j];
                to_sort[j] = to_sort[j + 1];
                to_sort[j + 1] = temp;
                temp_pair = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = temp_pair;
                swap_count++;
            }
        }
        if (swap_count == 0)
        {
            return;
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (!cycle_check(pairs[i].loser, pairs[i].winner))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }

    return;
}

// Print the winner of the election
void print_winner(void)
{
    bool is_locked;

    for (int i = 0; i < candidate_count; i++)
    {
        is_locked = false;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                is_locked = true;
            }
        }
        if (!is_locked)
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}

bool cycle_check(int loser_index, int start_position)
{
    if (loser_index == start_position)
    {
        return true;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser_index][i])
        {
            if (cycle_check(i, start_position))
            {
                return true;
            }
        }
    }
    return false;
}