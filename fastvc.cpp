/************************************************
** This is a local search solver for Minimum Vertex Cover.
************************************************/

/************************************************
** Date:	2015.2.2
** FastVC
** Author: Shaowei Cai, caisw@ios.ac.cn
**		   Key Laboratory of Computer Science,
**		   Institute of Software, Chinese Academy of Sciences,
**		   Beijing, China
************************************************/
#include "fastvc.h"

int try_step = 10;

int edge_cand;

void cover_LS() {
  int remove_v, add_v;
  int e, v1, v2;

  step = 1;

  while (1) {
    if (uncov_stack_fill_pointer == 0) // update best solution if needed
    {
      update_best_sol();
      // if (c_size==optimal_size) return;
      update_target_size();
      continue;
    }

    if (step % try_step == 0) // check cutoff
    {
      times(&finish);
      double elap_time = (finish.tms_utime + finish.tms_stime - start_time) /
                         sysconf(_SC_CLK_TCK);
      if (elap_time >= cutoff_time)
        return;
    }

    remove_v = choose_remove_v();
    // remove_dscore = dscore[remove_v];

    remove(remove_v);

    e = uncov_stack[rand() % uncov_stack_fill_pointer];
    v1 = edge[e].v1;
    v2 = edge[e].v2;

    if (dscore[v1] > dscore[v2] || (dscore[v1] == dscore[v2] && time_stamp[v1] < time_stamp[v2]))
      add_v = v1;
    else
      add_v = v2;

    add(add_v);

    int index = index_in_remove_cand[remove_v];
    index_in_remove_cand[remove_v] = 0;

    remove_cand[index] = add_v;
    index_in_remove_cand[add_v] = index;

    time_stamp[add_v] = time_stamp[remove_v] = step;
    // tabu_remove = add_v;
    // update_edge_weight();
    step++;
  }
}


int main(int argc, char *argv[]) {
  int i = 1;

  if(argc <= i) { cout << "c Missing argument" << endl; return -1; }
  input_format_with_size_information = false;
  if(argv[i] == "DIMACS") {
    input_format_with_size_information = true;
    i++;
  }

  if(argc <= i) { cout << "Missing argument" << endl; return -1; }
  cout << "c This is FastVC, solving instance " << argv[i] << endl;
  if (build_instance(argv[i++]) != 1) {
    cout << "c Cannot open instance file" << endl;
    return -1;
  }

  // optimal_size=0;
  int seed = 0;
  if(argc > i) sscanf(argv[i++], "%d", &seed);
  srand(seed);
  cout << "c seed " << seed << endl;

  cutoff_time = 0;
  if(argc > i) sscanf(argv[i++], "%d", &cutoff_time);
  cout << "c cutoff_time " << cutoff_time << endl;

  times(&start);
  start_time = start.tms_utime + start.tms_stime;

  init_sol();

  // if(c_size + uncov_stack_fill_pointer > optimal_size )
  //{
  // cout<<"c Start local search..."<<endl;
  cover_LS();
  //}

  // check solution
  if (check_solution() == 1) {
    // print_solution();
    cout << "c Best found vertex cover size = " << best_c_size << endl;
    cout << "c SearchSteps for best found vertex cover = " << best_step << endl;
    cout << "c SearchTime for best found vertex cover = " << best_comp_time << endl;
  }

  free_memory();
  return 0;
}
