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

class ray
{
public:
    ray() {}
    ray(const glm::dvec3 orig, glm::dvec3 dir, double tm = 0.0)
        : origin(orig), direction(dir), time(tm) {}
    
    glm::dvec3 origin;
    glm::dvec3 direction;
    double time;
};

double schlick(double cosine, double ref_idx) {
    auto r0 = (1-ref_idx) / (1+ref_idx);
    r0 = r0*r0;
    return r0 + (1-r0)*pow((1 - cosine),5);
}

// -----------------
class material; // forward declaration
struct hit_record
{
    glm::dvec3 point;
    glm::dvec3 normal;

   shared_ptr<material> mat_ptr; 

    bool front_face;

    inline void set_face_normal(const glm::dvec3& ray_org, const glm::dvec3& ray_dir, const glm::dvec3& outward_normal)
    {
        front_face = glm::dot(ray_dir, outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }

    double t;
};

// -----------------

class material  {
    public:
        virtual bool scatter(
            const ray& r_in, const hit_record& rec, glm::dvec3& attenuation, ray& scattered
        ) const = 0;
};

// -----------------

class dielectric : public material {
    public:
        dielectric(double ri) : ref_idx(ri) {}

        virtual bool scatter(
            const ray& r_in, const hit_record& rec, glm::dvec3& attenuation, ray& scattered
        ) const 
        {
            attenuation = glm::dvec3(1.0, 1.0, 1.0);
            double etai_over_etat = (rec.front_face) ? (1.0 / ref_idx) : (ref_idx);

            glm::dvec3 unit_direction = glm::normalize(r_in.direction);
            double cos_theta = fmin(glm::dot(-unit_direction, rec.normal), 1.0);
            double sin_theta = sqrt(1.0 - cos_theta*cos_theta);
            if (etai_over_etat * sin_theta > 1.0 ) {
                glm::dvec3 reflected = reflect(unit_direction, rec.normal);
                scattered = ray(rec.point, reflected);
                return true;
            }
            
            long unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();

            std::default_random_engine engine{seed};
            std::uniform_real_distribution<double> distribution{0, 1};

            double reflect_prob = schlick(cos_theta, etai_over_etat);
            if (distribution(engine) < reflect_prob)
            {
                glm::dvec3 reflected = reflect(unit_direction, rec.normal);
                scattered = ray(rec.point, reflected);
                return true;
            }

            glm::dvec3 refracted = refract(unit_direction, rec.normal, etai_over_etat);
            scattered = ray(rec.point, refracted);
            return true;
        }

    public:
        double ref_idx;
};


class lambertian : public material {
    public:
        lambertian(const glm::dvec3& a) : albedo(a) {}

        virtual bool scatter(
            const ray& r_in, const hit_record& rec, glm::dvec3& attenuation, ray& scattered
        ) const  
        {
            long unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();

            std::default_random_engine engine{seed};
            std::uniform_real_distribution<double> distribution{0, 6.28};
            std::uniform_real_distribution<double> distribution2{-1, 1};
           
            double a = distribution(engine);
            double z = distribution2(engine);
            double r = sqrt(1 - z*z);
            glm::dvec3 random_unit_vector = glm::dvec3(r*cos(a), r*sin(a), z);

            glm::dvec3 scatter_direction = rec.normal + random_unit_vector;
            scattered = ray(rec.point, scatter_direction);
            attenuation = albedo;
            return true;
        }

    public:
        glm::dvec3 albedo;
};


class metal : public material {
    public:
        metal(const glm::dvec3& a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {}

        virtual bool scatter(
            const ray& r_in, const hit_record& rec, glm::dvec3& attenuation, ray& scattered
        ) const  
        {
            // generate random in unit sphere
            glm::dvec3 random_in_unit_sphere;
            
            long unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();

            std::default_random_engine engine{seed};
            std::uniform_real_distribution<double> distribution{-1, 1};

            while(true)
            {
                random_in_unit_sphere = glm::dvec3(distribution(engine), distribution(engine), distribution(engine)); 
                if(pow(glm::length(random_in_unit_sphere), 2) >= 1.0) continue; 
            }

            glm::dvec3 reflected = reflect(glm::normalize(r_in.direction), rec.normal);
            scattered = ray(rec.point, reflected + fuzz*random_in_unit_sphere);
            attenuation = albedo;
            return (dot(scattered.direction, rec.normal) > 0);
        }

    public:
        glm::dvec3 albedo;
        double fuzz;
};


// -----------------

class camera {
    public:
        camera() : camera(glm::dvec3(0,0,-1), glm::dvec3(0,0,0), glm::dvec3(0,1,0), 40, 1, 0, 10) {}

        camera(
            glm::dvec3 lookfrom,
            glm::dvec3 lookat,
            glm::dvec3   vup,
            double vfov, // vertical field-of-view in degrees
            double aspect_ratio,
            double aperture,
            double focus_dist,
            double t0 = 0,
            double t1 = 0
        ) {
            auto theta = degrees_to_radians(vfov);
            auto h = tan(theta/2);
            auto viewport_height = 2.0 * h;
            auto viewport_width = aspect_ratio * viewport_height;

            w = glm::normalize(lookfrom - lookat);
            u = glm::normalize(glm::cross(vup, w));
            v = glm::cross(w, u);

            origin = lookfrom;
            horizontal = focus_dist * viewport_width * u;
            vertical = focus_dist * viewport_height * v;
            lower_left_corner = origin - horizontal/2.0 - vertical/2.0 - focus_dist*w;

            lens_radius = aperture / 2;
            time0 = t0;
            time1 = t1;
        }

        ray get_ray(double s, double t) const {
            long unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();

            std::default_random_engine engine{seed};
            std::uniform_real_distribution<double> distribution{-1, 1};
            std::uniform_real_distribution<double> distribution2{time0, time1};
           
            glm::dvec3 p;
            while(true)
            {
                p = glm::dvec3(distribution(engine), distribution(engine), 0.0);
                if(pow(glm::length(p), 2) >= 1.0) continue;
            }

            glm::dvec3 rd = lens_radius * p;
            glm::dvec3 offset = u * rd.x + v * rd.y;
            return ray(
                origin + offset,
                lower_left_corner + s*horizontal + t*vertical - origin - offset,
                distribution2(engine)
            );
        }

    private:
        glm::dvec3 origin;
        glm::dvec3 lower_left_corner;
        glm::dvec3 horizontal;
        glm::dvec3 vertical;
        glm::dvec3 u, v, w;
        double lens_radius;
        double time0, time1;  // shutter open/close times
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
    sphere(glm::dvec3 center, double rad, shared_ptr<material> m) : center_point(center), radius(rad), mat_ptr(m) {};

    virtual bool hit(const glm::dvec3& ray_org, const glm::dvec3& ray_dir, double t_min, double t_max, hit_record& rec) const;

public:
    glm::dvec3 center_point;
    double radius;
    shared_ptr<material> mat_ptr;
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

    GLuint display_texture;

    std::vector<std::vector<std::vector<glm::dvec3>>> model; // reference with model[x][y][sample]

    hittable_list world;

    int num_samples;
    int sample_count;
    long int total_time;

	void create_window();
	void gl_setup();
	void do_a_sample();
	
	void quit();
	
	bool pquit;
    bool send_tex = false;		



};

#endif
