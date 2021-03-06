#ifndef DECON_HPP
#define DECON_HPP
#include <vector>
#include <list>
#include <string>
#include <iostream>
#include <unordered_map>
#include <queue>
#include <stack>
#include "Variant.h"
#include "index.hpp"
#include "path.hpp"
#include "vg.hpp"
#include "vg.pb.h"
#include "Fasta.h"
#include "xg.hpp"
#include "position.hpp"
#include "vcfheader.hpp"


namespace vg{
    using namespace std;
    using namespace vcfh;
    class Deconstructor{
        public:

            Deconstructor();
            ~Deconstructor();
            void clear();
            void set_xg(string xg);
            void enumerate_path_names_in_index();
            void set_reference(string ref_file);
            void set_index(string ref_index);
            void set_graph(VG* v);
            void b_call(string pathname);
            map<string, vector<vcflib::Variant>> indel_caller(string pathname);

            /**
             * Project a path onto another path,
             * much like a projection of p2 onto p1 in space.
             */
             //list<Mapping> relative_mapping(Path& p1, Path& p2);

             map<string, vector<vcflib::Variant>> get_variants_on_paths_from_file(string pathfile);

             map<string, vector<vcflib::Variant>> get_variants_on_path(string pathname);
           /**
             * Build a vcf record from a mapping.
             */
            void mapping_to_simple_variant(string pathname, int64_t ref_id,
                                    list<Mapping> mappings, vector<vcflib::Variant>& variants);


            Mapping node_id_to_mapping(int64_t node_id);
            /**
             * Turn a vector of variants into a proper VCF.
             */
            void write_variants(string filename, map<string, vector<vcflib::Variant>> pathname_to_variants);

        private:
            // TODO Should be able to handle XG or VG indices
            string ref_index;
            string reference;
            string xg_file;
            VG* vgraph;
            vector<string> ref_paths;
            map<string, int64_t> inter_ref_and_index;
            map<int64_t, long> node_to_pos;
            int in_degree(Node n);
            bool on_ref(Node n, int64_t path);
            Node get_anchor_node(Node current, int64_t path);
            int inDegree(Node n);
            bool beenVisited(Node n, map<int64_t, int> node_to_level);
            Node get_alleles(Node n, int64_t path_id, map<int64_t, int>& node_to_level);
            map<int64_t, list<Mapping>> map_between_nodes(Node a, Node b);
            bool on_ref(int64_t node_id, int64_t path);
            map<int64_t, long> cache_path_positions(string pathname);
            pair< string, map<string, list<int64_t>>> parse_node_level_to_mutation(map<int64_t, int> node_to_level, Node anchor);

    };
}
#endif
