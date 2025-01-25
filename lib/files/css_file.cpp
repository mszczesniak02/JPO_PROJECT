#pragma once

#include "file.hpp"
#include "css_file.hpp"

// Function to count classes
void CSS_File::detect_classes(Statistics& stats) {
    //vector<string>& contents_=  get_contents();
    
    regex class_regex("\\.([a-zA-Z_-][a-zA-Z0-9_-]*)\\b");  // Matches .class but not numbers or units
    map<string, int> class_counts;

    for (const auto& line : contents_) {
        smatch match;
        string temp = line;

        while (regex_search(temp, match, class_regex)) {
            class_counts[match.str(1)]++;
            temp = match.suffix().str();
        }
    }

    stats.total_ = 0;
    for (const auto& [key, value] : class_counts) {
        stats.total_ += value;
    }

    vector<pair<string, int>> sorted_classes(class_counts.begin(), class_counts.end());
    sort(sorted_classes.begin(), sorted_classes.end(), [](const auto& a, const auto& b) {
        return b.second < a.second;
    });

    for (size_t i = 0; i < min<size_t>(5, sorted_classes.size()); ++i) {
        stats.param_.emplace_back(sorted_classes[i].first, sorted_classes[i].second);
    }
}
// Function to count CSS properties
void CSS_File::detect_properties( Statistics& stats) {
    regex property_regex("([a-zA-Z-]+)\\s*:");
    map<string, int> property_counts;

    for (const auto& line : contents_) {
        smatch match;
        string temp = line;

        while (regex_search(temp, match, property_regex)) {
            property_counts[match.str(1)]++;
            temp = match.suffix().str();
        }
    }

    stats.total_ = 0;
    for (const auto& [key, value] : property_counts) {
        stats.total_ += value;
    }

    vector<pair<string, int>> sorted_properties(property_counts.begin(), property_counts.end());
    sort(sorted_properties.begin(), sorted_properties.end(), [](const auto& a, const auto& b) {
        return b.second < a.second;
    });

    for (size_t i = 0; i < min<size_t>(5, sorted_properties.size()); ++i) {
        stats.param_.emplace_back(sorted_properties[i].first, sorted_properties[i].second);
    }
}

// Function to count pseudo-classes and pseudo-elements
void CSS_File::detect_pseudo_classes(Statistics& stats) {
    regex pseudo_class_regex(":([a-zA-Z0-9_-]+)\\b(?!:)");   // Matches :hover, :focus, etc.
    regex pseudo_element_regex("::([a-zA-Z0-9_-]+)");        // Matches ::before, ::after, etc.
    map<string, int> pseudo_counts;

    for (const auto& line : contents_) {
        smatch match;
        string temp = line;

        while (regex_search(temp, match, pseudo_class_regex)) {
            pseudo_counts[match.str(1)]++;
            temp = match.suffix().str();
        }

        temp = line;
        while (regex_search(temp, match, pseudo_element_regex)) {
            pseudo_counts[match.str(1)]++;
            temp = match.suffix().str();
        }
    }

    stats.total_ = 0;
    for (const auto& [key, value] : pseudo_counts) {
        stats.total_ += value;
    }

    vector<pair<string, int>> sorted_pseudo(pseudo_counts.begin(), pseudo_counts.end());
    sort(sorted_pseudo.begin(), sorted_pseudo.end(), [](const auto& a, const auto& b) {
        return b.second < a.second;
    });

    for (size_t i = 0; i < min<size_t>(5, sorted_pseudo.size()); ++i) {
        stats.param_.emplace_back(sorted_pseudo[i].first, sorted_pseudo[i].second);
    }
}

// Function to count media queries
void CSS_File::detect_media_queries(Statistics& stats) {
    regex media_query_regex("@media\\s*\\(([^\\)]+)\\)"); // Matches @media (condition)
    map<string, int> media_query_counts;

    for (const auto& line : contents_) {
        smatch match;
        string temp = line;

        while (regex_search(temp, match, media_query_regex)) {
            media_query_counts[match.str(1)]++;
            temp = match.suffix().str();
        }
    }

    stats.total_ = 0;
    for (const auto& [key, value] : media_query_counts) {
        stats.total_ += value;
    }

    vector<pair<string, int>> sorted_queries(media_query_counts.begin(), media_query_counts.end());
    sort(sorted_queries.begin(), sorted_queries.end(), [](const auto& a, const auto& b) {
        return b.second < a.second;
    });

    for (size_t i = 0; i < min<size_t>(5, sorted_queries.size()); ++i) {
        stats.param_.emplace_back(sorted_queries[i].first, sorted_queries[i].second);
    }
}
