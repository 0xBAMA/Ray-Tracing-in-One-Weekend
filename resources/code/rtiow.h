#ifndef SDF
#define SDF

#include "includes.h"


using std::shared_ptr;
using std::make_shared;
using std::sqrt;

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double degrees_to_radians(double degrees)
{
    return degrees * pi / 180.0;
}

struct hit_record
{
    glm::dvec3 point;
    glm::dvec3 normal;

    bool front_face;

    inline void set_face_normal(const glm::dvec3& ray_org, const glm::dvec3& ray_dir, const glm::dvec3& outward_normal)
    {
        front_face = glm::dot(ray_dir, outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }

    double t;
};

// -----------------

class hittable
{
public:
    virtual bool hit(const glm::dvec3& ray_org, const glm::dvec3& ray_dir, double t_min, double t_max, hit_record& rec) const = 0;
};

// -----------------

class sphere: public hittable
{
public:
    sphere(){};
    sphere(glm::dvec3 center, double rad) : center_point(center), radius(rad) {};

    virtual bool hit(const glm::dvec3& ray_org, const glm::dvec3& ray_dir, double t_min, double t_max, hit_record& rec) const;

public:
    glm::dvec3 center_point;
    double radius;
};

// -----------------

class hittable_list: public hittable
{
public:
    hittable_list(){};
    hittable_list(std::shared_ptr<hittable> object){add(object);}

    void clear(){objects.clear();}
    void add(std::shared_ptr<hittable> object){objects.push_back(object);}

    virtual bool hit(const glm::dvec3& ray_org, const glm::dvec3& ray_dir, double t_min, double t_max, hit_record& rec) const;

public:
    std::vector<std::shared_ptr<hittable>> objects;
};

// -----------------

class rtiow
{
public:

	rtiow();
	~rtiow();
	
private:

	SDL_Window * window;
	SDL_GLContext GLcontext;
	
	ImVec4 clear_color;
	
    GLuint display_shader;
    GLuint display_vao;
    GLuint display_vbo;

    std::vector<std::vector<std::vector<glm::vec3>>> model; // reference with model[x][y][sample]

    hittable_list world;

    int num_samples;
    int sample_count;
    long int total_time;

	void create_window();
	void gl_setup();
	void do_a_sample();
	
	void quit();
	
	bool pquit;
		
};

#endif
