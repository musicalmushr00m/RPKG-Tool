#include "rpkg_function.h"
#include "file.h"
#include "global.h"
#include "console.h"
#include "util.h"
#include <unordered_map>
#include <chrono>
#include <sstream>
#include <filesystem>

void
rpkg_function::extract_all_prim_model_from(std::string& input_path, std::string& filter, std::string& output_path)
{
    task_single_status = TASK_EXECUTING;
    task_multiple_status = TASK_EXECUTING;

    bool input_path_is_rpkg_file = false;

    if (std::filesystem::is_regular_file(input_path))
    {
        input_path_is_rpkg_file = true;
    }
    else
    {
        input_path = file::parse_input_folder_path(input_path);
    }

    if (!file::path_exists(input_path))
    {
        LOG_AND_EXIT("Error: The folder " + input_path + " to with the input RPKGs does not exist.");
    }

    if (!input_path_is_rpkg_file)
    {
        rpkg_function::import_rpkg_files_in_folder(input_path);
    }
    else
    {
        //rpkg_function::import_rpkg(input_path);

        std::filesystem::path base_folder_path = input_path;

        std::string parent_path = base_folder_path.parent_path().string();

        rpkg_function::import_rpkg_files_in_folder(parent_path);
    }

    std::stringstream ss;

    ss << "Scanning folder: Done";

    timing_string = ss.str();

    //LOG("\r" + ss.str() + std::string((80 - ss.str().length()), ' '));

    //file::create_directories(file::output_path_append("PRIM", output_path));

    std::vector<std::string> filters = util::parse_input_filter(filter);

    bool extract_single_hash = false;

    if (filters.size() == 1)
    {
        if (util::is_valid_hash(filters.at(0)))
        {
            extract_single_hash = true;
        }
    }

    uint64_t prim_count = 0;
    uint64_t prim_hash_size_total = 0;

    std::chrono::time_point start_time = std::chrono::high_resolution_clock::now();
    double console_update_rate = 1.0 / 2.0;
    int period_count = 1;

    for (auto& rpkg : rpkgs)
    {
        for (uint64_t r = 0; r < rpkg.hash_resource_types.size(); r++)
        {
            if (rpkg.hash_resource_types.at(r) == "PRIM")
            {
                for (uint64_t j = 0; j < rpkg.hashes_indexes_based_on_resource_types.at(r).size(); j++)
                {
                    uint64_t hash_index = rpkg.hashes_indexes_based_on_resource_types.at(r).at(j);

                    if (gui_control == ABORT_CURRENT_TASK)
                    {
                        return;
                    }

                    std::string hash_file_name =
                            util::uint64_t_to_hex_string(rpkg.hash.at(hash_index).hash_value) + "." +
                            rpkg.hash.at(hash_index).hash_resource_type;

                    std::chrono::time_point end_time = std::chrono::high_resolution_clock::now();

                    double time_in_seconds_from_start_time = (0.000000001 *
                                                              std::chrono::duration_cast<std::chrono::nanoseconds>(
                                                                      end_time - start_time).count());

                    if (time_in_seconds_from_start_time > console_update_rate)
                    {
                        start_time = end_time;

                        if (period_count > 3)
                        {
                            period_count = 0;
                        }

                        std::stringstream ss;

                        ss << "Scanning RPKGs for PRIM files" << std::string(period_count, '.');

                        timing_string = ss.str();

                        LOG_NO_ENDL("\r" << ss.str() << std::string((80 - ss.str().length()), ' '));

                        period_count++;
                    }

                    prim_hash_size_total += rpkg.hash.at(hash_index).data.resource.size_final;

                    prim_count++;
                }
            }
        }
    }

    ss.str(std::string());

    ss << "Scanning RPKGs for PRIM files: Done";

    LOG("\r" << ss.str() << std::string((80 - ss.str().length()), ' '));

    start_time = std::chrono::high_resolution_clock::now();
    int stringstream_length = 80;

    uint64_t prim_count_current = 0;
    uint64_t prim_hash_size_current = 0;

    std::string message = "Extracting PRIM MODEL to GLB/TGA files: ";

    if (!filter.empty())
    {
        LOG("Extracting PRIM MODEL to GLB/TGA files with filter \"" << filter << "\"");
    }

    std::unordered_map<std::string, uint32_t> prim_name_map;

    std::vector<std::string> found_in;
    std::vector<std::string> not_found_in;

    for (uint64_t z = 0; z < filters.size(); z++)
    {
        found_in.push_back("");

        not_found_in.push_back("");
    }

    for (auto& rpkg : rpkgs)
    {
        std::vector<bool> extracted;

        for (uint64_t z = 0; z < filters.size(); z++)
        {
            extracted.push_back(false);
        }

        if (rpkg.rpkg_file_path == input_path || !input_path_is_rpkg_file)
        {
            for (uint64_t r = 0; r < rpkg.hash_resource_types.size(); r++)
            {
                if (rpkg.hash_resource_types.at(r) == "PRIM")
                {
                    for (uint64_t j = 0; j < rpkg.hashes_indexes_based_on_resource_types.at(r).size(); j++)
                    {
                        uint64_t hash_index = rpkg.hashes_indexes_based_on_resource_types.at(r).at(j);

                        if (gui_control == ABORT_CURRENT_TASK)
                        {
                            return;
                        }

                        if (((prim_count_current * (uint64_t) 100000) / (uint64_t) prim_count) % (uint64_t) 10 ==
                            0 && prim_count_current > 0)
                        {
                            stringstream_length = console::update_console(message, prim_hash_size_total,
                                                                          prim_hash_size_current, start_time,
                                                                          stringstream_length);
                        }

                        prim_hash_size_current += rpkg.hash.at(hash_index).data.resource.size_final;

                        prim_count_current++;

                        if (!extract_single_hash || (extract_single_hash && filter == util::uint64_t_to_hex_string(
                                rpkg.hash.at(hash_index).hash_value)))
                        {
                            std::string hash_file_name =
                                    util::uint64_t_to_hex_string(rpkg.hash.at(hash_index).hash_value) + "." +
                                    rpkg.hash.at(hash_index).hash_resource_type;

                            bool found = false;

                            uint64_t input_filter_index = 0;

                            for (uint64_t z = 0; z < filters.size(); z++)
                            {
                                std::size_t found_position_hash = hash_file_name.find(filters.at(z));

                                if ((found_position_hash != std::string::npos && !filters.at(z).empty()))
                                {
                                    found = true;

                                    input_filter_index = z;

                                    break;
                                }
                            }

                            if (found || filter.empty())
                            {
                                std::string prim_output_dir = file::output_path_append(rpkg.rpkg_file_name,
                                                                                       output_path);

                                file::create_directories(prim_output_dir);

                                if (!filters.empty())
                                {
                                    extracted.at(input_filter_index) = true;
                                }

                                //std::cout << "rpkg_function::extract_prim_model_from(" << rpkgs.at(i).rpkg_file_path << ", " << util::uint64_t_to_hex_string(rpkgs.at(i).hash.at(hash_index).hash_value) << ", " << prim_output_dir << ");" << std::endl;

                                rpkg_function::extract_prim_model_from(rpkg.rpkg_file_path,
                                                                       util::uint64_t_to_hex_string(
                                                                               rpkg.hash.at(hash_index).hash_value),
                                                                       prim_output_dir);

                                /*std::vector<uint32_t>().swap(temp_entry_index);
                                std::vector<uint32_t>().swap(temp_logicalParent);
                                std::vector<uint32_t>().swap(temp_entityTypeResourceIndex);
                                std::vector<uint32_t>().swap(temp_propertyValues_start_offsets);
                                std::vector<uint32_t>().swap(temp_propertyValues_end_offsets);
                                std::vector<uint32_t>().swap(temp_postInitPropertyValues_start_offsets);
                                std::vector<uint32_t>().swap(temp_postInitPropertyValues_end_offsets);
                                std::vector<uint32_t>().swap(temp_platformSpecificPropertyValues_start_offsets);
                                std::vector<uint32_t>().swap(temp_platformSpecificPropertyValues_end_offsets);
                                std::vector<std::string>().swap(temp_property_types);
                                std::vector<std::vector<bool>>().swap(temp_property_types_shared);
                                std::vector<std::vector<uint32_t>>().swap(temp_property_types_shared_count);
                                std::vector<std::vector<uint32_t>>().swap(temp_property_types_offsets);
                                std::vector<std::vector<std::string>>().swap(temp_property_types_values);
                                std::vector<std::unordered_map<uint32_t, uint32_t>>().swap(temp_property_types_offsets_map);
                                std::vector<std::vector<uint32_t>>().swap(property_crc32_values);
                                std::vector<std::vector<uint32_t>>().swap(property_type_indexes);
                                std::vector<std::vector<uint32_t>>().swap(property_offsets);
                                std::vector<std::vector<uint32_t>>().swap(property_pointer_offsets);
                                std::vector<uint32_t>().swap(tblu_entry_index);
                                std::vector<uint32_t>().swap(tblu_logicalParent);
                                std::vector<uint32_t>().swap(tblu_entityTypeResourceIndex);
                                std::vector<uint64_t>().swap(tblu_entityId);
                                std::vector<uint32_t>().swap(tblu_editorOnly);
                                std::vector<std::string>().swap(tblu_entityName);
                                std::vector<char>().swap(temp_input_data);
                                std::vector<char>().swap(temp_output_data);
                                std::vector<char>().swap(tblu_input_data);
                                std::vector<char>().swap(tblu_output_data);
                                std::vector<matrix43>().swap(temp_world_coordinates);
                                std::vector<std::string>().swap(temp_world_coordinates_property_names);
                                std::unordered_map<uint32_t, uint32_t>().swap(temp_world_coordinates_map);*/
                            }
                        }
                    }
                }
            }
        }

        for (uint64_t z = 0; z < filters.size(); z++)
        {
            if (extracted.at(z))
            {
                if (found_in.at(z).empty())
                {
                    found_in.at(z).append(rpkg.rpkg_file_name);
                }
                else
                {
                    found_in.at(z).append(", " + rpkg.rpkg_file_name);
                }
            }
            else
            {
                if (not_found_in.at(z).empty())
                {
                    not_found_in.at(z).append(rpkg.rpkg_file_name);
                }
                else
                {
                    not_found_in.at(z).append(", " + rpkg.rpkg_file_name);
                }
            }
        }
    }

    std::chrono::time_point end_time = std::chrono::high_resolution_clock::now();

    ss.str(std::string());

    ss << message << "100% Done in "
       << (0.000000001 * std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count())
       << "s";

    LOG("\r" << ss.str() << std::string((80 - ss.str().length()), ' '));

    percent_progress = (uint32_t) 100;

    if (!filter.empty())
    {
        for (uint64_t z = 0; z < filters.size(); z++)
        {
            LOG(std::endl << "\"" << filters.at(z) << "\" was found in and extracted from: " << found_in.at(z));

            LOG(std::endl << "\"" << filters.at(z) << "\" was not found in RPKG file(s): " << not_found_in.at(z));
        }
    }

    task_single_status = TASK_SUCCESSFUL;
    task_multiple_status = TASK_SUCCESSFUL;
}