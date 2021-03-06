/*
 * Copyright (C) the libgit2 contributors. All rights reserved.
 *
 * This file is part of libgit2, distributed under the GNU GPL v2 with
 * a Linking Exception. For full terms see the included COPYING file.
 */
#ifndef INCLUDE_revwalk_h__
#define INCLUDE_revwalk_h__

#include "git2/revwalk.h"
#include "oidmap.h"
#include "commit_list.h"
#include "pqueue.h"
#include "pool.h"
#include "vector.h"

GIT__USE_OIDMAP;

struct git_revwalk {
	git_repository *repo;
	git_odb *odb;

	git_oidmap *commits;
	git_pool commit_pool;

	git_commit_list *iterator_topo;
	git_commit_list *iterator_rand;
	git_commit_list *iterator_reverse;
	git_pqueue iterator_time;

	int (*get_next)(git_commit_list_node **, git_revwalk *);
	int (*enqueue)(git_revwalk *, git_commit_list_node *);

	unsigned walking:1,
		first_parent: 1;
	unsigned int sorting;

	/* merge base calculation */
	git_commit_list_node *one;
	git_vector twos;
};

git_commit_list_node *git_revwalk__commit_lookup(git_revwalk *walk, const git_oid *oid);

#endif
